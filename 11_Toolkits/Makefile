CC = gcc
GLIB_CFLAGS  = `pkg-config --cflags glib-2.0`
CFLAGS = -Wall -g $(GLIB_CFLAGS)
LDFLAGS = `pkg-config --libs glib-2.0`


all: counter

counter: counter.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm counter || true


.PHONY: all clean