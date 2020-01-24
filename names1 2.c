/* 
 * names1.c - read in a list of names from stdin
 *   (separate readline() to a separate file)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: numbered list of names, one per line
 * 
 * David Kotz, April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

int main()
{
  const int maxNames = 100;  // maximum number of names
  const int maxLength = 50;  // maximum length of a name (minus 2)
  char names[maxNames][maxLength];
  int n = 0;		     // number of names read

  // read the list of names
  for (n = 0; n < maxNames && !feof(stdin); ) {
    if (readline(names[n], maxLength)) {
      n++; // only increment if no error
    }
  }

  printf("%d names\n", n);
  // print the list of names; note each name ends in newline.
  for (int i = 0; i < n; i++) {
    printf("%d: %s", i, names[i]);
  }
}
