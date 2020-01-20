/* 
 * pointer2 - a short program to demonstrate memory addresses.
 * 
 * CS50 January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
const int fifteen = 15;

void change(int *a, int b);

int main()
{
  // local variables are on the stack
  int x = 2, y = 5;

  // global variables; note they are in low memory addresses
  printf("globals\n");
  printf(" fifteen @ %p has value %d\n", (void *)&fifteen, fifteen);

  // main() is a function, and its code is at an address too!
  printf("main @ %p\n", (void *)main);

  // local variables are on the stack
  printf(" x @ %p has value %d\n", (void *)&x, x);
  printf(" y @ %p has value %d\n", (void *)&y, y);

  // pass x by reference, y by value
  change(&x,y);

  // see whether those changed
  printf("main @ %p\n", (void *)main);
  printf(" x @ %p has value %d\n", (void *)&x, x);
  printf(" y @ %p has value %d\n", (void *)&y, y);

  return 0;
}

void change(int *a, int b)
{
  // as above, change() is a function, and its parameters and local variables are on the stack
  printf("change @ %p\n", (void *)change);  
  printf(" a @ %p has value %d at %p\n", (void *)&a, *a, (void *)a);
  printf(" b @ %p has value %d\n", (void *)&b, b);
  // attempt to change the values
  *a = 99;
  b = 99;
}
