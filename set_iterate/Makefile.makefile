# Makefile for set_iterator examples
#
# usage (when you need to point Make at the library directory):
#  make -f set_iterate.makefile
# 
# David Kotz, May 2017
# Updated by Temi Prioleau, 2020

# our standard library
L = libcs50

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L
CC = gcc
MAKE = make

# Build both examples
all: set_iterate1 set_iterate2

# Note: Automatic variables
# $^ means the names of all dependencies
# $@ means the target file name
set_iterate1: set_iterate1.o $L/libcs50.a
	$(CC) $(CFLAGS) $^ -o $@

set_iterate2: set_iterate2.o $L/libcs50.a
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
set_iterate1.o: $L/set.h $L/memory.h
set_iterate2.o: $L/set.h $L/memory.h

.PHONY: test test1 test2 clean

test: test1 test2

test1: set_iterate1
	./set_iterate1

test2: set_iterate2
	./set_iterate2


# clean up after our compilation
clean:
	rm -f set_iterate1 set_iterate2 *~ *.o
