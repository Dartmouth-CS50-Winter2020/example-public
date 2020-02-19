# Makefile for 'tree' module
#
# David Kotz - April 2016, 2017

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = treetest
OBJS = treetest.o tree.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h
tree.o: tree.h

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -rf $(PROG).dSYM
	rm -f $(PROG)
