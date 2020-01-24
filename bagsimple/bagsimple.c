/*
 * bagsimple.c - a simple use case of bag module
 * 
 * read user names from stdin, insert names into a bag, and print 
 * out bag items
 * 
 * CS50 January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
#include "readlinep.h"

void nameprint(FILE *fp, void *item);
void namedelete(void *item);

int main()
{
	// create a bag
	bag_t *bag = bag_new(); // the bag

	// insert into the bag
	while (!feof(stdin)) {
		char *name = readlinep();
		if (name != NULL) {
			bag_insert(bag, name); 
		}
	}

	// print out bag items
	bag_print(bag, stdout, nameprint); 

	// delete the bag
	bag_delete(bag, namedelete);

	return 0;
}

// print a name 
void nameprint(FILE *fp, void *item)
{
	char *name = item; 
	if (name == NULL) {
		fprintf(fp, "(null)");
	}
	else {
		fprintf(fp, "%s", name); 
	}
}

// delete a name 
void namedelete(void *item)
{
	if (item != NULL) {
		free(item); 
	}
}

