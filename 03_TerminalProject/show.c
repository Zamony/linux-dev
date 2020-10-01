#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define WIN_POS 1
#define WIN_PAD 2
#define KEY_ESCAPE 27

void print_win_line(WINDOW *win, FILE *f, int width) {
    if (feof(f)) {
        return;
    }

    char buf[width];
    memset(buf, 0, width);
    
    fgets(buf, width, f);
    wprintw(win, "%s", buf);
}

void show(const char *filename, FILE *f) {
    initscr();
    noecho();
    cbreak();
    printw("File: %s", filename);
    refresh();

    WINDOW *out_win = newwin(LINES-WIN_PAD, COLS-WIN_PAD, WIN_POS, WIN_POS);
    box(out_win, 0, 0);
    wrefresh(out_win);

    int rows = LINES-2*WIN_PAD;
    int cols = COLS-2*WIN_PAD;
    WINDOW *win = newwin(rows, cols, 2*WIN_POS, 2*WIN_POS);

    keypad(win, TRUE);
    scrollok(win, TRUE);

    for (int i = 0; i < rows-1; i++) {
        print_win_line(win, f, cols);
    }

    wrefresh(win);
    int c = wgetch(win);
    while (c != KEY_ESCAPE) {
        if (c == ' ') {
            print_win_line(win, f, cols);
            wrefresh(win);
        }
        c = wgetch(win);
    }

    endwin();
}


int main(int argc, const char *argv[]) {

    if (argc != 2) {
        printf("usage: show filename\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("unable to open file '%s'\n", argv[1]);
        return 2;
    }

    show(argv[1], f);

    fclose(f);

    return 0;
}