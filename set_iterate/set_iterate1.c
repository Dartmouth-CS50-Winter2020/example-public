/* 
 * set_iterate1.c - test program for simple set module
 *
 * David Kotz - April 2016, updated May 2016, 2017
 * Updated by Temi Prioleau, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"

static void set_merge(set_t *setA, set_t *setB);
static void set_merge_helper(void *arg, const char *key, void *item);
static void itemprint(FILE *fp, const char *key, void *item);

int main() 
{
  set_t *setA, *setB, *result;     // three sets

  setA = assertp(set_new(), "setA");
  setB = assertp(set_new(), "setB");
  result = assertp(set_new(), "result");

  printf("Empty result set: ");
  set_print(result, stdout, itemprint);
  putchar('\n');
  
  printf("Building set A: ");
  set_insert(setA, "Brown", "http://www.brown.edu");
  set_insert(setA, "Dartmouth", "http://www.dartmouth.edu");
  set_insert(setA, "Yale", "http://www.yale.edu");
  set_insert(setA, "Harvard", "http://www.harvard.edu");
  set_insert(setA, "Princeton", "http://www.princeton.edu");
  set_insert(setA, "Columbia", "http://www.columbia.edu");
  set_print(setA, stdout, itemprint);
  putchar('\n');
  
  printf("Building set B: ");
  set_insert(setB, "Penn", "http://www.upenn.edu");
  set_insert(setB, "Dartmouth", "http://www.dartmouth.edu");
  set_insert(setB, "Cornell", "http://www.cornell.edu");
  set_insert(setB, "Stanford", "http://www.stanford.edu");
  set_insert(setB, "Princeton", "http://www.princeton.edu");
  set_insert(setB, "Duke", "http://www.duke.edu");
  set_print(setB, stdout, itemprint);
  putchar('\n');
  
  printf("\nMerge of setA into result: \n");
  set_merge(result, setA);
  set_print(result, stdout, itemprint);
  putchar('\n');

  printf("\nMerge of setB into result: \n");
  set_merge(result, setB);
  set_print(result, stdout, itemprint);
  putchar('\n');

  printf("\nDelete the sets...\n");
  set_delete(setA, NULL);
  set_delete(setB, NULL);
  set_delete(result, NULL);
}

/* Merge the second set into the first set;
 * the second set is unchanged.
 */
static void 
set_merge(set_t *setA, set_t *setB)
{
  set_iterate(setB, setA, set_merge_helper);
}

/* Consider one item for insertion into the other set.
 */
static void 
set_merge_helper(void *arg, const char *key, void *item)
{
  set_t *setA = arg;

  if (set_insert(setA, key, item))
    printf("\t%s added\n", key);
  else
    printf("\t%s exists\n", key);

}

/* Print the given item to the given file.
 * We just print the key; item is unused.
 */
static void 
itemprint(FILE *fp, const char *key, void *item)
{
  if (key == NULL)
    fprintf(fp, "(null), ");
  else 
    fprintf(fp, "%s, ", key);
}
