/* 
 * names3.c - read in a list of names from stdin
 *   (array of pointers; use of readlinep)
 *   (drop support for command-line filename arguments)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: numbered list of names, one per line
 * 
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "readlinep.h"

/* ********************************************************* */
int main()
{
  const int maxNames = 100;  // maximum number of names
  char *names[maxNames];      // array of names, each a pointer to string
  int n = 0;		      // number of names read

  // read the list of names
  for (n = 0; n < maxNames && !feof(stdin); ) {
    char *name = readlinep();
    if (name != NULL) {
      names[n] = name;
      n++; // only increment if no error
    }
  }

  printf("%d names\n", n);
  // print the list of names, and free as we go
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, names[i]);
    free(names[i]);
  }
}
