# Makefile for 'tree' module
#  (unit testing)
#
# David Kotz - May 2016, April 2017
# updated by Xia Zhou, July 2016
# updated by Temi Prioleau, 2020

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb # -DTESTING
PROG = treetest
OBJS = treetest.o tree.o memory.o readlinep.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h readlinep.h
tree.o: tree.h memory.h
memory.o: memory.h
readlinep.o: readlinep.h

.PHONY: test unittest unit clean

test: $(PROG)
	./$(PROG)

unittest: tree.h tree.c memory.h unittest.h memory.o
	$(CC) $(CFLAGS) -DUNIT_TEST tree.c memory.o -o unittest

unit:	unittest
	./unittest


clean:
	rm -f *~
	rm -f *.o
	rm -rf *.dSYM
	rm -f $(PROG)
	rm -f unittest
