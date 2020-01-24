/* 
 * pointer0 - characters, and character pointers.
 * 
 * CS50 January 2019
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c = 'x';		      // a character
  char *p = &c;		      // a pointer to a character
  char **pp = &p;	      // a pointer to a pointer to a character

  printf("c  = '%c'\n", c);
  printf("p  = %p, *p = '%c'\n", p, *p);
  printf("pp = %p, *pp = %p, **pp = '%c'\n", (void *)pp, *pp, **pp);

  return 0;
}
