/** @file guess.c
 * Main game file
 *
 * Simple number guessing game
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>
#include <stdbool.h>

#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define ROMAN_CNT 101
#define MAX_ROMAN_SIZE 64


static char roman[ROMAN_CNT][MAX_ROMAN_SIZE] = {
    "",
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII",
    "XIII",
    "XIV",
    "XV",
    "XVI",
    "XVII",
    "XVIII",
    "XIX",
    "XX",
    "XXI",
    "XXII",
    "XXIII",
    "XXIV",
    "XXV",
    "XXVI",
    "XXVII",
    "XXVIII",
    "XXIX",
    "XXX",
    "XXXI",
    "XXXII",
    "XXXIII",
    "XXXIV",
    "XXXV",
    "XXXVI",
    "XXXVII",
    "XXXVIII",
    "XXXIX",
    "XL",
    "XLI",
    "XLII",
    "XLIII",
    "XLIV",
    "XLV",
    "XLVI",
    "XLVII",
    "XLVIII",
    "XLIX",
    "L",
    "LI",
    "LII",
    "LIII",
    "LIV",
    "LV",
    "LVI",
    "LVII",
    "LVIII",
    "LIX",
    "LX",
    "LXI",
    "LXII",
    "LXIII",
    "LXIV",
    "LXV",
    "LXVI",
    "LXVII",
    "LXVIII",
    "LXIX",
    "LXX",
    "LXXI",
    "LXXII",
    "LXXIII",
    "LXXIV",
    "LXXV",
    "LXXVI",
    "LXXVII",
    "LXXVIII",
    "LXXIX",
    "LXXX",
    "LXXXI",
    "LXXXII",
    "LXXXIII",
    "LXXXIV",
    "LXXXV",
    "LXXXVI",
    "LXXXVII",
    "LXXXVIII",
    "LXXXIX",
    "XC",
    "XCI",
    "XCII",
    "XCIII",
    "XCIV",
    "XCV",
    "XCVI",
    "XCVII",
    "XCVIII",
    "XCIX",
    "C",
};

/**
 * Convert a number @p n to roman number
 * @param n should be in the range [1..100]
 * @returns The return value is a string corresponding
 * to the provided value or NULL if invalid value provided
 */
char * to_roman(int n) {
    if (n >= ROMAN_CNT || n < 1) {
        return NULL;
    }

    return roman[n];
}


/**
 * Convert a roman number @p number to decimal number
 * @param number is a string, representing a roman number
 * @returns The return value is an integer in the range [1..100]
 * corresponding to the provided value
 * or negative number if invalid input provided
 */
int from_roman(char *number) {
    for (int i = 1; i < ROMAN_CNT; i++) {
        if (strcmp(roman[i], number) == 0) {
            return i;
        }
    }

    return -1;
}


static bool is_roman_mode(int argc, char ** argv) {
    return argc == 2 && strcmp(argv[1], "-r") == 0;
}

static bool is_version_mode(int argc, char ** argv) {
    return argc == 2 && strcmp(argv[1], "--version") == 0;
}


static bool is_help_mode(int argc, char ** argv) {
    return argc != 1 && !is_roman_mode(argc, argv);
}

static void print_help() {
    printf("%s", _(
        "Guess is a simple terminal game\n\n"
        "Usage: guess [OPTION]\n\n"
        "Options:\n"
        "   -r  enable roman number mode\n"
        "   --help  print this help, then exit\n"
        "   --version  print version number, then exit\n\n"
        "It is a simple game where you choose a number "
        "in the range [1, 100] and the computer finds it "
        "by shrinking the remaining range by the factor of two\n\n"
    ));
}


int main(int argc, char ** argv) {
    setlocale (LC_ALL, "");
    bindtextdomain ("guess", LOCALE_PATH);
    textdomain("guess");

    if (is_version_mode(argc, argv)) {
        printf("guess %s\n", VERSION);
        return 0;
    }

    if (is_help_mode(argc, argv)) {
        print_help();
        return 0;
    }

    const bool is_roman = is_roman_mode(argc, argv);
    if (is_roman) {
        printf(_("Choose a number in the range [I..C]\n"));
    } else {
        printf(_("Choose a number in the range [1..100]\n"));
    }

    int l = 1;
    int r = 100;
    while (l < r) {
        const int mid = (l + r) / 2;
        if (is_roman) {
            printf(_("Is your number greater than %s? (%s/%s):"), to_roman(mid), _("y"), _("n"));
        } else {
            printf(_("Is your number greater than %d? (%s/%s):"), mid, _("y"), _("n"));
        }

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

    if (is_roman) {
        printf(_("Your number is %s\n"), to_roman(l));
    } else {
        printf(_("Your number is %d\n"), l);
    }

    return 0;
}