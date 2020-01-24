/* 
 * pointer1 - a short program to demonstrate pointers.
 * 
 * CS50 January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *CS = "CS50";

int main()
{
  printf(" CS = %p, *CS = '%c', CS as string = '%s'\n", CS, *CS, CS);

  for (char *p = CS; *p != '\0'; p++) {
    printf(" p = %p, *p = '%c'\n", p, *p);
  }

  return 0;
}
