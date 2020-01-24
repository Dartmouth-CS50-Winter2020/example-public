# Makefile for 'tree' module
#  (added targets for 'make test' and 'make stocks')
#  (added readlinep.o and readlinep.h)
#
# David Kotz - April 2016, 2017

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -DTESTING
PROG = treetest
OBJS = treetest.o tree.o memory.o readlinep.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h readlinep.h
tree.o: tree.h memory.h
memory.o: memory.h
readlinep.o: readlinep.h

.PHONY: test clean

test: $(PROG) stocks
	./$(PROG) < stocks

stocks:
	 curl 'http://download.finance.yahoo.com/d/quotes.csv?s=NKE,AAPL,MCD,TWTR,IBM,YHOO,ORCL,GOOG,MSFT,NFLX,FB&f=spl1v&e=.csv' > stocks

clean:
	rm -f *~
	rm -f *.o
	rm -rf $(PROG).dSYM
	rm -f $(PROG)
	rm -f stocks
