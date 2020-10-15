#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#ifndef REGEX_USE_UTF
#define REGEX_USE_UTF 0
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>

#include "regex.h"


RegexMatch *regex_new_match(int index, int width, char *buf) {
    RegexMatch *m = calloc(1, sizeof(RegexMatch));
    m->next = NULL;
    m->index = index;
    m->width = width;
    memcpy(m->buf, buf, MAXSTR);
    
    return m;
}

void regex_free_match(RegexMatch *match) {
    RegexMatch *curr = match;
    while (curr != NULL) {
        RegexMatch *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}


RegexMatchStatus regex_match(char *regex, char *str, RegexMatch **match) {
    pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR)regex;
    subject = (PCRE2_SPTR)str;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

    if (REGEX_USE_UTF == 1) {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
    } else {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
    }

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        return RegexCompileError;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        RegexMatchStatus status;
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            status = RegexNoMatchError;
            break;
        default:
            status = RegexMatchError;
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return status;
    }

    ovector = pcre2_get_ovector_pointer(match_data);
    RegexMatch *curr = NULL;
    for (i = 0; i < rc; i++) {
        char buf[MAXSTR] = {0};
        snprintf(buf, sizeof(buf), "%s", subject + ovector[2*i]);
        int width = (int)(ovector[2*i+1] - ovector[2*i]);
        if (curr == NULL) {
            *match = regex_new_match(ovector[2*i], width, buf);
            curr = *match;
        } else {
            curr->next = regex_new_match(ovector[2*i], width, buf);
            curr = curr->next;
        }
    }

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return RegexMatchSuccess;
}
