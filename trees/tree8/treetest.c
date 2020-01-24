/* 
 * treetest.c - test program for simple binary-tree module
 *   (not a very good test program)
 *
 * David Kotz - April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void myprint(FILE *fp, const char *key, void *string);

int main() 
{
  tree_t *tree;		      // the tree
  char datastring[] = "Test data";

  tree = tree_new();
  if (tree == NULL) {
    printf("tree_new failed\n");
    exit(1);
  }

  // some simple test code
  tree_insert(tree, "charlene", datastring);
  tree_insert(tree, "hillary", datastring);
  tree_insert(tree, "irina", datastring);
  tree_insert(tree, "alice", datastring);
  tree_insert(tree, "eve", datastring);
  tree_insert(tree, "bob", datastring);
  tree_insert(tree, "david", datastring);
  tree_insert(tree, "fred", datastring);
  tree_insert(tree, "george", datastring);
  tree_insert(NULL, 0, datastring); // should be ignored

  printf("find %s returns %s\n", "irina", (char*) tree_find(tree, "irina"));
  printf("find %s returns %s\n", "eve", (char*) tree_find(tree, "eve"));

  printf("update node %s...\n", "eve");
  tree_insert(tree, "eve", "new string");
  printf("find %s returns %s\n", "eve", (char*) tree_find(tree, "eve"));
  printf("find null returns %s\n", (char*) tree_find(NULL, "eve"));
  
  printf("\nThe tree:\n");
  tree_print(tree, stdout, myprint);

  printf("\ndelete the tree...\n");
  tree_delete(tree, NULL);
  printf("done\n");
}

/* print the given string to the given file */
void myprint(FILE *fp, const char *key, void *string)
{
  fprintf(fp, "[%s]: '%s'", key, (char*)string);
}

