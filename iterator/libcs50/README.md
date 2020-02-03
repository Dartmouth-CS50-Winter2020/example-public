# CS50 Tiny Search Engine (TSE) utility library

David Kotz, April 2016, 2017.
Xia Zhou, July 2016.

These modules support the TSE project.  Feel free to drop in your implementation of the data-structure modules, but **do not change any of the other source files in this directory.**

## Usage
To build `libcs50.a`, run `make`. 
The starter kit includes two pre-built libraries:

 * `libcs50.a-Darwin` is for MacOS (may not work on all MacOS versions)
 * `libcs50.a-Linux` is for Linux, built on standard CS50 servers 

If you prefer our data-structure implementation over your own, modify the Makefile to replace the rule for `$(LIB)`:

```
$(LIB):
	cp $(LIB)-`uname` $(LIB)
```
Notice that just copies the relevant pre-compiled library to `libcs50.a`.

To clean up, run `make clean`.

## Overview

 * bag - the *bag* data structure from Lab 3
 * counters - the *counters* data structure from Lab 3
 * file - functions to read files (includes readlinep)
 * hashtable - the *hashtable* data structure from Lab 3
 * jhash - the Jenkins Hash function used by hashtable
 * memory - handy wrappers for malloc/free
 * set - the *set* data structure from Lab 3
 * webpage - functions to load and scan web pages
