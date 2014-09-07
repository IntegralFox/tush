CC=gcc
CFLAGS=-c -Wall -g
LFLAGS=-o tush

all: tush

tush: tush.o histlist.o
	$(CC) $(LFLAGS) tush.o histlist.o

tush.o: tush.c histlist.h
	$(CC) $(CFLAGS) tush.c

histlist.o: histlist.h histlist.c
	$(CC) $(CFLAGS) histlist.c

clean:
	rm -rf *o tush
