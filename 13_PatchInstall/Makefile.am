AM_CFLAGS = -std=c99 -Wall -Wextra
AM_CPPFLAGS = -D LOCALEDIR='"$(localedir)"'

bin_PROGRAMS=guess
guess_SOURCES=guess.c

pkgdata_DATA=ru/LC_MESSAGES/guess.mo
pkgdatadir = $(localedir)/ru/LC_MESSAGES

ru/LC_MESSAGES/guess.mo: mo

mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt $< -o ru/LC_MESSAGES/guess.mo

update:
	xgettext -k_ -c guess.c -o update.pot
	msgmerge -U guess.pot update.pot
	msgmerge -U ru.po guess.pot

clean:
	rm -rf ru     || true
	rm update.pot || true
	rm guess      || true

.PHONY: update clean mo