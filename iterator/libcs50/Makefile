# Makefile for CS50 library
#   Builds and compiles all these utility functions into a library.
#
# David Kotz, April 2016, July 2017
# updated by Xia Zhou, July 2016, July 2018

# object files, and the target library
OBJS = bag.o counters.o file.o hashtable.o jhash.o memory.o \
       set.o webpage.o
LIB = libcs50.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = #-DNOSLEEP # -DMEMTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

# Build the library by archiving object files
# 	ar cr $(LIB) $(OBJS)
#	
$(LIB):
	cp $(LIB)-`uname` $(LIB)

# Dependencies: object files depend on header files
bag.o: bag.h
counters.o: counters.h
file.o: file.h
hashtable.o: hashtable.h set.h jhash.h 
jhash.o: jhash.h
memory.o: memory.h
set.o: set.h
webpage.o:  webpage.h memory.h file.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o
