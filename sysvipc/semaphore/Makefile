CC=gcc
CFLAGS=-Wall -g -O2
OBJECTS=n1.o n2.o p1.o p2.o s8.o s9.o sem0.o
LIBRARIES=
PROGRAMS=n1 n2 p1 p2 s8 s9 sem0
LDLIBS=

.PHONY:         all clean

all:            $(OBJECTS) $(LIBRARIES) $(PROGRAMS)

clean:
	rm -f *.o *.a $(PROGRAMS)
