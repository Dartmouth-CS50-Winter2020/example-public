/* 
 * tree.c - simple binary-tree module
 *  (introduces typedef)
 *
 * David Kotz - April 2016, 2017
 * Xia Zhou, July 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/**************** global variables ****************/

const int TREE_KEY_NOT_FOUND = -1; // used by tree_find()

/**************** types ****************/
typedef struct treenode {
  int key;		      // search key for this item
  int data;		      // data for this item
  struct treenode *left, *right; // children
} tree_t;

/**************** functions ****************/

/**************** tree_new() ****************/
/* Create a new tree for the given key and data;
 * return NULL if error.
 */
tree_t *
tree_new(const int key, const int data)
{
  tree_t *node = malloc(sizeof(tree_t));

  if (node == NULL) {
    return NULL;
  } else {
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
  }
}

/**************** tree_insert() ****************/
/* Insert into the given tree, or NULL to start a new tree;
 * wherein the item is described by a key and some data,
 * and the tree is provided as a pointer to its root;
 * providing a NULL root creates a new tree and returns it.
 * If the key is already in the tree, its datum is update with new data;
 * the key should not be TREE_KEY_NOT_FOUND.
 */
tree_t *
tree_insert(tree_t *node, const int key, const int data)
{
  if (node == NULL) {
    // tree is empty; create and return a new node
    return tree_new(key, data);
  } else if (key == node->key) {
    // key already exists; update the data
    node->data = data;
    return node;
  } else {
    // recursively insert either left or right,
    // and update our child pointers if needed
    if (key < node->key) {
      node->left = tree_insert(node->left, key, data);
    } else {
      node->right = tree_insert(node->right, key, data);
    }
    return node;
  }
}

/**************** tree_find() ****************/
/* Return the data associated with the given key;
 * return TREE_KEY_NOT_FOUND if key is not in tree.
 */
int 
tree_find(tree_t *node, const int key)
{
  if (node == NULL) {
    return TREE_KEY_NOT_FOUND;
  } else if (key == node->key) {
    return node->data;
  } else {
    if (key < node->key) {
      return tree_find(node->left, key);
    } else {
      return tree_find(node->right, key);
    }
  }
}

