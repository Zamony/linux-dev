#include <locale.h>
#include <ncurses.h>
#include "regex.h"

#define DX 3
#define ONLELINE 3

void display_error(WINDOW *win, int status) {
	if (status == RegexCompileError) {
		wprintw(win, "  Compile error\n\n");
	}
	
	if (status == RegexNoMatchError) {
		wprintw(win, "  No matches\n\n");
	}

	if (status == RegexMatchError) {
		wprintw(win, "  Matching error\n\n");
	}
}

void main() {
	setlocale(LC_ALL, "");
	WINDOW *winA, *winB, *winO;
	char inA[MAXSTR], inB[MAXSTR];
	int c = 0;
	int half;

	initscr();
	cbreak();
	printw("Input:");
	refresh();

	half = (COLS-2*DX)/2;
	winA = newwin(ONLELINE, half, DX, DX);
	winB = newwin(ONLELINE, half, DX, DX+half);
	winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
	keypad(winA, TRUE);
	keypad(winB, TRUE);
	scrollok (winO, TRUE);
	wmove(winO, 1, 0);
	do {
		werase(winA); box(winA, 0, 0);
		mvwgetnstr(winA, 1, 1, inA, MAXSTR);
		werase(winB); box(winB, 0, 0);
		mvwgetnstr(winB, 1, 1, inB, MAXSTR);
		wprintw(winO, "  `%s`: `%s`\n", inA, inB);
		RegexMatch *m = NULL;
		int status = regex_match(inA, inB, &m);
		if (status == RegexMatchSuccess) {
			for (RegexMatch *c = m; c != NULL; c=c->next) {
				wprintw(winO, "  %d: %.*s\n", c->index, c->width, c->buf);
			}
		} else {
			display_error(winO, status);
		}
		regex_free_match(m);
		wprintw(winO, "\n");
		box(winO, 0, 0);
		wrefresh(winO);
	} while(*inA);

	endwin();
}
