/* 
 * names7.c - read in a list of names from stdin
 *   (remove duplicates)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: sorted list of names, one per line
 * 
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "readlinep.h"

// A structure for each node in linked list
struct listnode {
  char *name;
  struct listnode *next;
};

bool list_insert(struct listnode *headp, char *name);
struct listnode *listnode_new(char *name);
void listnode_delete(struct listnode *node);

/* ********************************************************* */
int main()
{
  struct listnode head = {NULL, NULL}; // dummy node at head of empty list
  int n = 0;			       // number of names read

  // read the list of names - any number of names!
  while (!feof(stdin)) {
    char *name = readlinep();
    if (name != NULL) {
      if (list_insert(&head, name)) {
	n++; // only increment if no error
      }
    }
  }

  // remove duplicates from list
  for (struct listnode *node = head.next; node != NULL; ) {
    if (node->next != NULL && strcmp(node->name, node->next->name) == 0) {
      // duplicate detected; remove node->next from list
      struct listnode *duplicate = node->next;
      node->next = node->next->next;
      free(duplicate->name);
      listnode_delete(duplicate);
      n--;
    } else {
      // only advance when we do not find a duplicate
      node = node->next;
    }
  }
  
  printf("%d names:\n", n);
  // print the list of names
  for (struct listnode *node = head.next; node != NULL; node = node->next)
    printf("%s\n", node->name);

  // here we are lazy and do not free the list. 

  return 0;
}

/* *************************************************
 * list_insert: insert the given name into the list, in alphabetical order.
 * Return true if success, false if failure.
 */
bool list_insert(struct listnode *headp, char *name) 
{
  struct listnode *node = listnode_new(name);

  if (headp == NULL || node == NULL) {
    return false;
  } else {
    // insert the new node at alphabetical place in list
    struct listnode *place = headp;
    // slide along the list to the right place
    while (place->next != NULL && strcmp(name, place->next->name) > 0) {
      place = place->next;
    }
    // On exit, place points at last item on the list, or 
    // place points at a middle item, but new name comes before place->next.
    // Thus, we want to insert 'node' after place and before place->next.
    node->next = place->next;
    place->next = node;
  }
  return true;
}


/* *************************************************
 * listnode_new: create a new node to store the given name.
 * Returns pointer to new node, if successful, else returns NULL.  
 * The pointer 'name' is assumed to be malloc storage, and is not copied.
 * Caller is responsibe for later deleting 'name'.
 * Caller is responsible for later calling listnode_delete(node).
 */
struct listnode *listnode_new(char *name) 
{
  // allocate memory for the new node
  struct listnode *node = malloc(sizeof(struct listnode));
  
  if (node == NULL) {
    return NULL;
  } else {
    // initialize node contents
    node->next = NULL;
    node->name = name;
  }

  return node;
}

/* *************************************************
 *  listnode_delete: delete memory for the given node.
 */
void listnode_delete(struct listnode *node)
{
  if (node != NULL) {
    if (node->name != NULL)
      free(node->name);
    free(node);
  }
}
