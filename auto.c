/*
 *
 *   File: auto.c
 *
 *   Description: Illustrates the auto local variables
 *
 *   Code taken from pg. 336 (Program 7.2) (Bronson) "First Book on ANSI C"
 *
 * */
#include <stdio.h>

void testauto(); /* function prototype */

int main()
{
  int count; /* create the auto variable count */
  for (count = 1; count <= 3; count++ )
    testauto();
  return 0;
}

void testauto()
{
  int num = 0; /* create the auto variable num */
	       /* and initialize it to zero */
  printf("The value of the automatic variable num is %d\n", num);
  num++;
}
