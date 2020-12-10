#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

#include "config.h"

#define _(STRING) gettext(STRING)


int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    bindtextdomain ("guess", LOCALEDIR);
    textdomain("guess");

    printf(_("Guess a number in the range [1..100]\n"));

    int l = 1;
    int r = 100;
    while (l < r) {
        const int mid = (l + r) / 2;
        printf(_("Is your number greater than %d? (%s/%s):"), mid, _("y"), _("n"));
        char buf[10] = {0};
        int p = scanf("%8s", buf);
        if (p < 1) {
            printf(_("Invalid input\n"));
            exit(1);
        }

        if (strcmp(buf, _("y")) == 0) {
            l = mid + 1;
            continue;
        }

        if (strcmp(buf, _("n")) == 0) {
            r = mid;
            continue;
        }
    }

    printf(_("Your number is %d\n"), l);

    return 0;
}