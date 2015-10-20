CC=gcc
CFLAGS=-g -Wall -Werror -ansi -pedantic -I../include
LFLAGS=-L../lib

all: lib main

../lib/libp.so.1.0: rev.o pdot.o pdash.o
	ld -shared -soname libp.so.1 -o ../lib/libp.so.1.0 rev.o pdot.o pdash.o

lib: ../lib/libp.so.1.0

rev.o: rev.c ../include/rev.h
	$(CC) $(CFLAGS) -fPIC -c rev.c

pdot.o: pdot.c ../include/pdot.h
	$(CC) $(CFLAGS) -fPIC -c pdot.c

pdash.o: pdash.c ../include/pdash.h
	$(CC) $(CFLAGS) -fPIC -c pdash.c

main: main.c
	$(CC) $(CFLAGS) $(LFLAGS) main.c -lp -o main

clean:
	rm -f ../lib/libp.so.1.0
	rm -f *.o
	rm -f main
