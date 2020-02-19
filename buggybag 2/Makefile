# Makefile for the "bagsimple" program that uses the "bag" module.
#
# CS50 January 2019

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = bagsimple
OBJS = bagsimple.o bag.o readlinep.o
LIBS = -lm

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# object file's dependency of user-defined header files
bagsimple.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h

.PHONY: clean

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
