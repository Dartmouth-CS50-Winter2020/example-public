# Makefile for http client-server example
#
# David Kotz, May 2016
# Temi Prioleau, 2020

PROGS = httpclient httpserver
LIBS = 
LLIBS = 

FLAGS = # 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### httpclient ##################
httpclient: httpclient.o file.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

httpclient.o: file.h

########### httpserver #################
httpserver: httpserver.o file.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

httpserver.o: file.h

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 
