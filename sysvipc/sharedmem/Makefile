CC=gcc
CFLAGS=-Wall -g -O2
OBJECTS=mem1.o mem2.o shm1.o shm2.o sharedmem2.o sharedmem3.o
OBJECTS+=s1.o s2.o s3.o s3x.o s3y.o s4.o s4a.o
LIBRARIES=
PROGRAMS=mem1 mem2 shm1 shm2 sharedmem2 sharedmem3
PROGRAMS+=s1 s2 s3 s3x s3y s4 s4a
LDLIBS=

.PHONY:         all clean

all:            $(OBJECTS) $(LIBRARIES) $(PROGRAMS)

clean:
	rm -f *.o *.a $(PROGRAMS)
