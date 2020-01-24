/* 
 * tree.h - header file for simple binary-tree module
 *  (version 4: separate tree from treenode)
 *
 * David Kotz - April 2016, 2017
 */

#ifndef __TREE_H
#define __TREE_H

/**************** global types ****************/
typedef struct tree tree_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) tree;
 * return NULL if error.
 */
tree_t *tree_new(void);

/* Insert item into the given tree; NULL tree is ignored.
 * The item is described by a key and some data.
 */
void tree_insert(tree_t *tree, const int key, void *data);

/* Return the data associated with the given key;
 * return NULL if tree is NULL or if key is not found.
 */
void *tree_find(tree_t *tree, const int key);

#endif // __TREE_H
