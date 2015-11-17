CC=gcc
CFLAGS=-Wall -g -O2
OBJECTS=popen1.o popen2.o popen3.o
OBJECTS+=pipe1.o pipe2.o pipe3.o 
OBJECTS+=p-stdio1.o p-stdio2.o p-stdio3.o
OBJECTS+=t-write1.o t-write2.o t-write3.o
OBJECTS+=s1.o s2.o reverse.o 
OBJECTS+=two-pipe1.o t1.o t2.o t3.o
LIBRARIES=
PROGRAMS=popen1 popen2 popen3
PROGRAMS+=pipe1 pipe2 pipe3
PROGRAMS+=p-stdio1 p-stdio2 p-stdio3 
PROGRAMS+=t-write1 t-write2 t-write3
PROGRAMS+=s1 s2 reverse
PROGRAMS+=two-pipe1 t1 t2 t3
LDLIBS=

.PHONY:         all clean

all:            $(OBJECTS) $(LIBRARIES) $(PROGRAMS)

clean:
	rm -f *.o *.a $(PROGRAMS)
