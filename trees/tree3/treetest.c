/* 
 * treetest.c - test program for simple binary-tree module
 *   (not a very good test program)
 * 
 * David Kotz - April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* Use a global variable to hold the root of tree;
 * it does not need to be global, in this simple example,
 * but here it serves an example of a global variable.
 * We normally try hard to avoid using globals.
 */
tree_t *root;

int main() 
{
  char datastring[] = "Test data";

  // some simple test code
  root = tree_insert(root, 3, datastring);
  root = tree_insert(root, 4, datastring);
  root = tree_insert(root, 1, datastring);
  root = tree_insert(root, 5, datastring);
  root = tree_insert(root, 6, datastring);
  root = tree_insert(root, 2, datastring);
  root = tree_insert(root, 8, datastring);
  root = tree_insert(root, 7, datastring);
  root = tree_insert(root, 0, datastring);

  printf("find %d returns %s\n", 4, tree_find(root, 4));
  printf("find %d returns %s\n", 5, tree_find(root, 5));

  printf("update node %d...\n", 5);
  root = tree_insert(root, 5, "new string");
  printf("find %d returns %s\n", 5, tree_find(root, 5));
}
