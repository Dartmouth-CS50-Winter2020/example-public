# Makefile for 'tree' module
#  (added memory module, -DTESTING for tree.c)
#
# David Kotz - April 2016, 2017

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -DTESTING
PROG = treetest
OBJS = treetest.o tree.o memory.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h
tree.o: tree.h memory.h
memory.o: memory.h

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -rf $(PROG).dSYM
	rm -f $(PROG)
