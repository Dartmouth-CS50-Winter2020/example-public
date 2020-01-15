/*
 * atoi - read an integer from each argument,
 *        and print them to stdout.  catch errors.
 *
 * usage: atoi [integer]...
 *
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char *argv[])
{
  int status = 0;
  int number;         // the number converted from argv[1]
  char excess;        // any excess chars after the number

  for (int i = 1; i < argc; i++) {
    // if the argument is valid, sscanf should extract exactly one thing.
    if (sscanf(argv[i], "%d%c", &number, &excess) == 1) {
      printf("argument %d: %d\n", i, number);
    } else {
      fprintf(stderr, "argument %d: '%s' is not a valid integer\n", 
	      i, argv[i]);
      status++;
    }
  }

  return status;  // return the number of invalid arguments
}
