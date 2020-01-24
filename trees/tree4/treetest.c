/* 
 * treetest.c - test program for simple binary-tree module
 *   (not a very good test program)
 * 
 * David Kotz - April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() 
{
  tree_t *tree;		      // the tree
  char datastring[] = "Test data";

  tree = tree_new();

  // some simple test code
  tree_insert(tree, 3, datastring);
  tree_insert(tree, 4, datastring);
  tree_insert(tree, 1, datastring);
  tree_insert(tree, 5, datastring);
  tree_insert(tree, 6, datastring);
  tree_insert(tree, 2, datastring);
  tree_insert(tree, 8, datastring);
  tree_insert(tree, 7, datastring);
  tree_insert(tree, 0, datastring);
  tree_insert(NULL, 0, datastring); // should be ignored

  printf("find %d returns %s\n", 4, tree_find(tree, 4));
  printf("find %d returns %s\n", 5, tree_find(tree, 5));

  printf("update node %d...\n", 5);
  tree_insert(tree, 5, "new string");
  printf("find %d returns %s\n", 5, tree_find(tree, 5));
  printf("find null returns %s\n", tree_find(NULL, 5));
}
