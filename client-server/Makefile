# Makefile for socket examples
#
# David Kotz, May 2016
# Xia Zhou, August 2017
# Temi Prioleau, 2020

PROGS = inclient inserver inserver-fork
LLIBS = 

FLAGS = # 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### inclient ##################
inclient: inclient.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

inclient.o: 

########### inserver #################
inserver: inserver.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

inserver.o: 

########### inserver-fork #################
inserver-fork: inserver-fork.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

inserver-fork.o: 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 
