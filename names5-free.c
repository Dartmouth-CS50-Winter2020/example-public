/* 
 * names5.c - read in a list of names from stdin
 *   (linked list version of names3.c)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: list of names, one per line
 * 
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
  
  printf("%d names:\n", n);
  // print the list of names
  for (struct listnode *node = head.next; node != NULL; node = node->next)
    printf("%s\n", node->name);

  // delete the list
  struct listnode *next = NULL; 
  for (struct listnode *node = head.next; node != NULL; )
  {
    next = node->next; 
    if (node->name != NULL) {
      free(node->name);
    }
    free(node);
    node = next; 
  } 

  return 0;
}

/* *************************************************
 * list_insert: insert the given name into the list.
 * Return true if success, false if failure.
 */
bool list_insert(struct listnode *headp, char *name) 
{
  struct listnode *node = listnode_new(name);

  if (headp == NULL || node == NULL) {
    return false;
  } else {
    // insert the new node at head of the list
    node->next = headp->next;
    headp->next = node;
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

