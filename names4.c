/* 
 * names4.c - read in a list of names from stdin
 *   (sort names; void*; casting)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: sorted and numbered list of names, one per line
 * 
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readlinep.h"

/* string-comparison function usable with qsort() */
int strcmpp(const void* a, const void* b);

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

  // sort the list with quicksort
  qsort(names, n, sizeof(char*), strcmpp);

  printf("%d names\n", n);
  // print the list of names, and free as we go
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, names[i]);
    free(names[i]);
  }
}

/* 
 * strcmpp: like strcmp but args passed as char** instead of char*,
 * compatible with qsort.  Cast each argument as needed.
 * from http://arstechnica.com/civis/viewtopic.php?f=20&t=607813
 */
int strcmpp(const void* a, const void* b)
{
  return strcmp(*((char**) a), *((char**) b));
}
