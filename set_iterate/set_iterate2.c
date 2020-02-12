/* 
 * set_iterate2.c - test program for simple set module
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
static void itemdelete(void *item);
static int *intsave(int item);

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
  set_insert(setA, "Brown", intsave(10));
  set_insert(setA, "Dartmouth", intsave(20));
  set_insert(setA, "Yale", intsave(15));
  set_insert(setA, "Harvard", intsave(8));
  set_insert(setA, "Princeton", intsave(5));
  set_insert(setA, "Columbia", intsave(1));
  set_print(setA, stdout, itemprint);
  putchar('\n');
  
  printf("Building set B: ");
  set_insert(setB, "Penn", intsave(7));
  set_insert(setB, "Dartmouth", intsave(11));
  set_insert(setB, "Cornell", intsave(9));
  set_insert(setB, "Stanford", intsave(6));
  set_insert(setB, "Princeton", intsave(3));
  set_insert(setB, "Duke", intsave(12));
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
  set_delete(setA, itemdelete);
  set_delete(setB, itemdelete);
  set_delete(result, itemdelete);
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
 * If the other set does not contain the item, insert it;
 * otherwise, update the other set's item with sum of item values.
 */
static void 
set_merge_helper(void *arg, const char *key, void *item)
{
  set_t *setA = arg;
  int *itemB = item;
  
  // find the same key in setA
  int *itemA = set_find(setA, key);
  if (itemA == NULL) {
    // not found: insert it
    set_insert(setA, key, intsave(*itemB));
    printf("\t%s added\n", key);
  } else {
    // add to the existing value
    *itemA += *itemB;
    printf("\t%s exists\n", key);
  }
}

/* print the given item to the given file.
 */
static void 
itemprint(FILE *fp, const char *key, void *item)
{
  int *countp = item;
  int count = *countp;

  if (key == NULL)
    fprintf(fp, "(null), ");
  else 
    fprintf(fp, "%s=%d, ", key, count);
}

static int *
intsave(int item)
{
  int *saved = assertp(malloc(sizeof(int)), "intsave");
  *saved = item;
  return saved;
}

static void 
itemdelete(void *item)
{
  if (item != NULL)
    free(item);
}
