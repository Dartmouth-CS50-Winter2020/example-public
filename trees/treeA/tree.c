/* 
 * tree.c - simple binary-tree module
 *  (version A: unit testing)
 *
 * David Kotz, April-May 2016, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "memory.h"

/**************** file-local global variables ****************/

/**************** local types ****************/
typedef struct treenode {
  char *key;		           // search key for this item
  void *data;		           // pointer to data for this item
  struct treenode *left, *right;   // children
} treenode_t;

/**************** global types ****************/
typedef struct tree {
  struct treenode *root;                     // root of the tree
} tree_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see tree.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static treenode_t *tree_insert_helper(treenode_t *node, 
				      const char *key, void *data);
static treenode_t *treenode_new(const char *key, void *data);
static void *tree_find_helper(treenode_t *node, const char *key);
static void tree_print_helper(tree_t *tree, treenode_t *node, int depth,
			      FILE *fp,
 			      void (*itemprint)(FILE *fp, const char *key, void *data) );

static void tree_delete_helper(tree_t *tree, treenode_t *node,
			       void (*itemdelete)(void *data) );

/**************** tree_new() ****************/
tree_t *
tree_new(void)
{
  tree_t *tree = count_malloc(sizeof(tree_t));

  if (tree == NULL) {
    return NULL; // error allocating tree
  } else {
    // initialize contents of tree structure
    tree->root = NULL;
    return tree;
  }
}

/**************** tree_insert() ****************/
void
tree_insert(tree_t *tree, const char *key, void *data)
{
  if (tree != NULL) {
    tree->root = tree_insert_helper(tree->root, key, data);
  }
 
#ifdef TESTING
  count_report(stdout, "After tree_insert");
#endif
}


/**************** tree_insert_helper() ****************/
/* Recursively find the place to insert the new node;
 * if 'node' is NULL it returns pointer to new node.
 */
static treenode_t *  // not visible outside this file
tree_insert_helper(treenode_t *node, const char *key, void *data)
{
  if (node == NULL) {
    // tree is empty; create and return a new node
    return treenode_new(key, data);
  } else if (strcmp(key, node->key) == 0) {
    // key already exists; update the data
    node->data = data;
    return node;
  } else {
    // recursively insert either left or right,
    // and update our child pointers if needed
    if (strcmp(key, node->key) < 0) {
      node->left = tree_insert_helper(node->left, key, data);
    } else {
      node->right = tree_insert_helper(node->right, key, data);
    }
    return node;
  }
}

/**************** treenode_new ****************/
/* Allocate and initialize a treenode */
static treenode_t * // not visible outside this file
treenode_new(const char *key, void *data)
{
  treenode_t *node = count_malloc(sizeof(treenode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key = count_malloc(strlen(key)+1);
    if (node->key == NULL) {
      // error allocating memory for key; 
      // cleanup and return error
      count_free(node);
      return NULL;
    } else {
      strcpy(node->key, key);
      node->data = data;
      node->left = NULL;
      node->right = NULL;
      return node;
    }
  }
}

/**************** tree_find() ****************/
void *
tree_find(tree_t *tree, const char *key)
{
  if (tree == NULL) {
    return NULL;
  } else {
    return tree_find_helper(tree->root, key);
  }
}

/**************** tree_find_helper() ****************/
/* Recursive function to find a node holding this key, 
 * return data for the found node, or NULL if not found.
 */
static void * // not visible outside this file
tree_find_helper(treenode_t *node, const char *key)
{
  if (node == NULL) {
    return NULL;
  } else if (strcmp(key, node->key) == 0) {
    return node->data;
  } else {
    if (strcmp(key, node->key) < 0) {
      return tree_find_helper(node->left, key);
    } else {
      return tree_find_helper(node->right, key);
    }
  }
}

/**************** tree_print() ****************/
void
tree_print(tree_t *tree, FILE *fp, 
 	   void (*itemprint)(FILE *fp, const char *key, void *data) )
{
  if (tree != NULL) {
    tree_print_helper(tree, tree->root, 0, fp, itemprint);
  }
}

/**************** tree_print_helper() ****************/
/* Recursive function to print nodes of the tree, 
 * return data for the found node, or NULL if not found.
 */
static void  // not visible outside this file
tree_print_helper(tree_t *tree, treenode_t *node, int depth, FILE *fp, 
 		  void (*itemprint)(FILE *fp, const char *key, void *data) )
{
  if (node != NULL) {
    // print the left subtree
    tree_print_helper(tree, node->left, depth+1, fp, itemprint);
    
    // print the current node
    fprintf(fp, "%*s", depth+1, " ");	// indent one space per depth
    if (itemprint != NULL) {		// print the node
      (*itemprint)(fp, node->key, node->data); 
    }
    fputc('\n', fp);			// print a newline

    // print the right subtree
    tree_print_helper(tree, node->right, depth+1, fp, itemprint);
  }
  return;
}

/**************** tree_delete() ****************/
void 
tree_delete(tree_t *tree, void (*itemdelete)(void *data) )
{
  if (tree != NULL) {
    tree_delete_helper(tree, tree->root, itemdelete);
  }
  count_free(tree);

#ifdef TESTING
  count_report(stdout, "End of tree_delete");
#endif
}

/**************** tree_delete_helper() ****************/
/* Recursive function to delete nodes of the tree.
 */
static void  // not visible outside this file
tree_delete_helper(tree_t *tree, treenode_t *node,
 		   void (*itemdelete)(void *data) )
{
  if (node != NULL) {
    // delete the left subtree
    tree_delete_helper(tree, node->left, itemdelete);

    // delete the right subtree
    tree_delete_helper(tree, node->right, itemdelete);
    
    // delete the current node
    if (itemdelete != NULL) {	 // but first...
      (*itemdelete)(node->data); // delete its contents
    }
    count_free(node->key);
    count_free(node);
  }
  return;
}

/********************************************************
 **************** unit testing **************************
 ********************************************************/

#ifdef UNIT_TEST
#include "unittest.h"

/////////////////////////////////////
// create and validate an empty tree
int test_newtree0()
{
  START_TEST_CASE("newtree0");
  tree_t *tree = tree_new();
  EXPECT(tree != NULL);
  EXPECT(tree->root == NULL);

  EXPECT(tree_find(tree, "hello") == NULL);

  tree_delete(tree, NULL);
  EXPECT(count_net() == 0);

  END_TEST_CASE;
  return TEST_RESULT;
}

/////////////////////////////////////
// create and validate a tree with one item
int test_newtree1()
{
  START_TEST_CASE("newtree1");
  tree_t *tree = tree_new();
  EXPECT(tree != NULL);
  int data = 5;
  tree_insert(tree, "abcd", &data);
  EXPECT(tree->root != NULL);
  EXPECT(strcmp(tree->root->key, "abcd") == 0);
  EXPECT(tree->root->data == &data);
  EXPECT(tree->root->left == NULL);
  EXPECT(tree->root->right == NULL);

  EXPECT(tree_find(tree, "abcd") == &data);
  EXPECT(tree_find(tree, "hello") == NULL);

  tree_delete(tree, NULL);
  EXPECT(count_net() == 0);
  END_TEST_CASE;
  return TEST_RESULT;
}

/////////////////////////////////////
// create and validate a tree with long left branch
int test_treeleft()
{
  START_TEST_CASE("treeleft");
  tree_t *tree = tree_new();
  EXPECT(tree != NULL);
  int a,b,c,d;
  tree_insert(tree, "d", &d);
  tree_insert(tree, "c", &c);
  tree_insert(tree, "b", &b);
  tree_insert(tree, "a", &a);
  EXPECT(tree->root != NULL);
  EXPECT(tree->root->left != NULL);
  EXPECT(tree->root->left->left != NULL);
  EXPECT(tree->root->left->left->left != NULL);
  EXPECT(strcmp(tree->root->key, "d") == 0);
  EXPECT(strcmp(tree->root->left->key, "c") == 0);
  EXPECT(strcmp(tree->root->left->left->key, "b") == 0);
  EXPECT(strcmp(tree->root->left->left->left->key, "a") == 0);
  EXPECT(tree->root->right == NULL);
  EXPECT(tree->root->left->right == NULL);
  EXPECT(tree->root->left->left->right == NULL);
  EXPECT(tree->root->left->left->left->right == NULL);

  EXPECT(tree_find(tree, "a") == &a);
  EXPECT(tree_find(tree, "b") == &b);
  EXPECT(tree_find(tree, "c") == &c);
  EXPECT(tree_find(tree, "d") == &d);
  EXPECT(tree_find(tree, "e") == NULL);

  tree_delete(tree, NULL);
  EXPECT(count_net() == 0);
  END_TEST_CASE;
  return TEST_RESULT;
}

void test_dataprint(FILE *fp, const char *key, void *data)
{
  fprintf(fp, "%s(%d)", key, *(int *)data);
}

/////////////////////////////////////
// create a few nodes and test tree_find and tree_print
int test_treefind()
{
  START_TEST_CASE("treefind");
  tree_t *tree = tree_new();
  EXPECT(tree != NULL);

  int dave = 4; tree_insert(tree, "dave", &dave);
  EXPECT(tree_find(tree, "dave") == &dave);

  int ann = 1;  tree_insert(tree, "ann", &ann);
  int bob = 2;  tree_insert(tree, "bob", &bob);
  int cheri = 3; tree_insert(tree, "cheri", &cheri);
  EXPECT(tree_find(tree, "ann") == &ann);
  EXPECT(tree_find(tree, "bob") == &bob);
  EXPECT(tree_find(tree, "cheri") == &cheri);
  EXPECT(tree_find(tree, "dave") == &dave);
  EXPECT(tree_find(tree, "fred") == NULL);

  tree_print(tree, stdout, test_dataprint);

  tree_delete(tree, NULL);
  EXPECT(count_net() == 0);
  END_TEST_CASE;
  return TEST_RESULT;
}

////////////////////////////////////////////
int
main(const int argc, const char *argv[])
{
  int failed = 0;

  failed += test_newtree0();
  failed += test_newtree1();
  failed += test_treeleft();
  failed += test_treefind();

  if (failed) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}

#endif // UNIT_TEST
