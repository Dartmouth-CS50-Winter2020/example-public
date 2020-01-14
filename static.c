/*

  File: static.c

  Description: Illustrates the use of auto variables, with `static`.


   Revised code taken from pg. 336 (Program 7.2) (Bronson) "First Book on ANSI C"

*/ 


#include <stdio.h>

void teststat(); /* function prototype */

int main()
{
  int count; /* count is a local auto variable */

  for(count = 1; count <= 3; count++)
    teststat();

  return 0;
}

/*  Note, that the varuable num in teststat() is only set to zero once. The value set by 
    the local scope static variable num detains its value when teststat() returns.
*/

void teststat()
{
  static int num=0; /* num is a local static variable */

  printf("The value of the static variable num is now %d\n", num);
  num++;

}
