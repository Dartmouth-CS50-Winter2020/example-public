# Makefile for the "bagsimple" program that uses the "bag" module.
#
# CS50 January 2020

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = bagsimple
OBJS = bagsimple.o bag.o readlinep.o
LIBS = -lm

.PHONY: all clean

all: bagsimple

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

# object files depend on include files
bagsimple.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
