CC=gcc
CFLAGS=-Wall -g -O2
OBJECTS=m1.o m2.o m3s.o m3c.o m3m.o m3c2.o
LIBRARIES=
PROGRAMS=m1 m2 m3s m3c m3m m3c2
LDLIBS=

.PHONY:         all clean

all:            $(OBJECTS) $(LIBRARIES) $(PROGRAMS)

clean:
	rm -f *.o *.a $(PROGRAMS)
