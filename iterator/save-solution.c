/*
 * save.c - an example of saving hashtable items into an external file
 * 
 * usage: ./save FileName
 *
 * Xia Zhou, Winter 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "libcs50/hashtable.h"
#include "libcs50/counters.h"
#include "libcs50/memory.h"

/**************** local function prototypes ****************/
hashtable_t* init_hashtable();
static void ct_delete(void *item); 
void save_item (void *arg, const char *key, void *item);
void save_counts (void *arg, const int key, int count); 

/**************** main ****************/
int main(const int argc, char *argv[])
{
	char* program = argv[0];  // program name

	// check input arguments: # of arguments
	if (argc != 2) {
		fprintf(stderr, "usage: %s FileName\n", program);
		return 1; 
	}

	// create and initialize hashtable content
	hashtable_t* ht = init_hashtable(); 
	if (ht == NULL) {
		fprintf(stderr, "%s: failed to init hashtable\n", program);
		return 2;
	}

	// save hashtable content to an external file 
	FILE *fp = fopen(argv[1], "w");
	if (fp == NULL) {
		fprintf(stderr, "%s: failed to open file%s\n", program, argv[1]);
		return 3;
	}
	hashtable_iterate(ht, fp, save_item);
	fclose(fp); 

	// clean up
	hashtable_delete(ht, ct_delete);
	return 0;
}

/**************** initialize hashtable content ****************/
hashtable_t* init_hashtable()
{
	hashtable_t* ht = assertp(hashtable_new(10), "new hashtable");

	char* name1 = "wonder woman";
	counters_t *ct1 = assertp(counters_new(), "new counters");
	counters_set(ct1, 3, 6); // insert dummy counters items
	counters_set(ct1, 4, 8);
	hashtable_insert(ht, name1, ct1); 

	return ht; 
}

/******** delete counters item ********/
static void ct_delete(void *item)
{
	counters_t* ct = item;

	if (ct != NULL) {
		counters_delete(ct);
	}
}

/******** helper to save item in hashtable ********/
void save_item (void *arg, const char *key, void *item)
{
	FILE *fp = arg; 
	counters_t *c = item;

	fprintf(fp, "%s:", key);
	counters_iterate(c, fp, save_counts);
	fprintf(fp, "\n");
}

/******** helper to save items in counters ********/
void save_counts (void *arg, const int key, int count)
{
	FILE *fp = arg; 
	fprintf(fp, " %d %d", key, count);
}