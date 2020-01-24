/* 
 * treetest.c - test program for simple binary-tree module
 *   (interesting item, print/delete functions, and malloc/free tracking)
 *
 * usage:
 *   read stock quotes from stdin to use as test item.
 * each line should be comma-separated values, with 
 *  "symbol",close,price,volume
 * where close and price are floats and volume is an int.
 * for example, pipe the output of curl into this program:
 *  curl 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL,GOOG,MSFT,FB&f=spl1v&e=.csv' | ./treetest
 * Old documentation about that API:
 *  http://www.financialwisdomforum.org/gummy-stuff/Yahoo-data.htm
 *  http://www.marketindex.com.au/yahoo-finance-api
 *
 * David Kotz - April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "readlinep.h"

struct stock {
  float close;		      // previous close
  float price;		      // last trade price
  int volume;		      // trading volume
};

static void stockprint(FILE *fp, const char *key, void *item);
static void stockdelete(void *item);
static int stockcount = 0;

int main() 
{
  tree_t *tree;		      // the tree

  tree = tree_new();
  if (tree == NULL) {
    printf("tree_new failed\n");
    exit(1);
  }

  printf("\ntesting tree_insert:\n");
  // read stocks from stdin and insert each into the tree
  while (!feof(stdin)) {
    struct stock *stp = malloc(sizeof(struct stock));

    if (stp == NULL) {
      printf("out of memory for stocks\n");
    } else {
      // parsing the input line, each with format:
      // "symbol",low,high,volume
      char symbol[8];
      char *line = readlinep();
      if (line != NULL) {
	sscanf(line, "\"%[^\"]\",%f,%f,%d", symbol, &stp->close, &stp->price, &stp->volume);
	printf("%s,%f,%f,%d\n", symbol, stp->close, stp->price, stp->volume);
	tree_insert(tree, symbol, stp);
	stockcount++;
	free(line);
      } else {
	free(stp);
      }
    }
  }

  printf("\ntesting tree_find:\n");
  stockprint(stdout, "IBM", tree_find(tree, "IBM")); putchar('\n');
  stockprint(stdout, "NKE", tree_find(tree, "NKE")); putchar('\n');
  stockprint(stdout, "YHOO", tree_find(tree, "YHOO")); putchar('\n');

  printf("update node %s...\n", "YHOO");
  tree_insert(tree, "YHOO", NULL); // this will leak memory
  printf("update tree_find(%s):\n", "YHOO");
  stockprint(stdout, "YHOO", tree_find(tree, "YHOO")); putchar('\n');
  
  printf("\nThe tree:\n");
  tree_print(tree, stdout, stockprint);

  printf("\ndelete the tree...\n");
  tree_delete(tree, stockdelete);
  printf("done, with %d stocks still allocated\n", stockcount);
}

/* print the given item to the given file.
 * in our test, key is the same as item->symbol
 */
static void stockprint(FILE *fp, const char *key, void *item)
{
  struct stock *stp = item;
  if (stp == NULL)
    fprintf(fp, "[%s]: (null)", key);
  else 
    fprintf(fp, "[%s]: close %f, price %f, vol %d", 
	    key, stp->close, stp->price, stp->volume);
}

static void stockdelete(void *item)
{
  if (item) {
    free(item);
  }
  stockcount--;
}

