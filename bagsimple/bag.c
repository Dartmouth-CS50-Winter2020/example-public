/*
 * bag.c -- a simplified version of bag module
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"


// local data types
typedef struct bagnode {
	void *item; 
	struct bagnode *next; 
} bagnode_t;

// global data types
typedef struct bag {
	struct bagnode *head; 
} bag_t;

// global functions 

/*** bag_new()*****/
bag_t *bag_new(void)
{
	bag_t *bag = malloc(sizeof(bag_t));

	if (bag == NULL) {
		return NULL;
	} else {
		bag->head = NULL;
		return bag; 
	}
}

/*** bag_insert()****/
void bag_insert(bag_t *bag, void *item)
{
	if (bag != NULL && item != NULL) {
		bagnode_t *new = malloc(sizeof(bagnode_t)); 

		if (new != NULL) {
			new->item = item; 
			new->next = bag->head;
			bag->head = new; 
		}
	}
}

/**************** bag_extract() ****************/
void *bag_extract(bag_t *bag)
{
  if (bag == NULL) {
    return NULL; // bad bag
  } else if (bag->head == NULL) {
    return NULL; // bag is empty
  } else {
    bagnode_t *out = bag->head; // the node to take out
    void *item = out->item;	// the item to return
    bag->head = out->next;	// hop over the node to remove
    free(out);
    return item;
  }
}

/**************** bag_print() ****************/
void
bag_print(bag_t *bag, FILE *fp, void (*itemprint)(FILE *fp, void *item) )
{
  if (fp != NULL) {
    if (bag != NULL) {
      fputc('{', fp);
      for (bagnode_t *node = bag->head; node != NULL; node = node->next) {
        // print this node
        if (itemprint != NULL) {  // print the node's item 
          (*itemprint)(fp, node->item); 
          fputc(',', fp);
        }
      }
      fputs("}\n", fp);
    } else {
      fputs("(null)\n", fp);
    }
  }
}

/**************** bag_delete() ****************/
void 
bag_delete(bag_t *bag, void (*itemdelete)(void *item) )
{
  if (bag != NULL) {
    for (bagnode_t *node = bag->head; node != NULL; ) {
      if (itemdelete != NULL) {		    // if possible...
        (*itemdelete)(node->item);	    // delete node's item
      }
      bagnode_t *next = node->next;	    // remember what comes next
      free(node);			    // free the node
      node = next;			    // and move on to next
    }

    free(bag);
  }
}



