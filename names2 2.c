/* 
 * names2.c - read in a list of names from stdin
 *   (read from a file named in argument)
 *
 * usage: names [filename]
 * filename: includes list of names, one per line
 * stdin: used if filename not specified
 * stdout: numbered list of names, one per line
 * 
 * David Kotz, April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "freadline.h"

int main(const int argc, char *argv[])
{
  const int maxNames = 100;  // maximum number of names
  const int maxLength = 50;  // maximum length of a name (minus 2)
  char names[maxNames][maxLength];
  FILE *fp;		      // input file
  int n = 0;		      // number of names read

  // validate arguments and open input file
  if (argc == 1) {
    fp = stdin;
  } else if (argc == 2) {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      fprintf(stderr, "%s cannot open file '%s'\n", argv[0], argv[1]);
      exit (2);
    } 
  } else {
    fprintf(stderr, "usage: %s [filename]\n", argv[0]);
    exit (1);
  }

  // read the list of names
  for (n = 0; n < maxNames && !feof(fp); ) {
    if (freadline(fp, names[n], maxLength)) {
      n++; // only increment if no error
    }
  }

  fclose(fp);

  printf("%d names\n", n);
  // print the list of names; note each name ends in newline.
  for (int i = 0; i < n; i++) {
    printf("%d: %s", i, names[i]);
  }
}
