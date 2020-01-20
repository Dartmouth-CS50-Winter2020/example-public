/* 
 * pointer3 - a short program to demonstrate memory addresses.
 * 
 * CS50 January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *hello = "hello world!";
  char buf[15];

  strcpy(buf, "something"); // initialize buf

  // local variables are on the stack
  printf(" hello @ %p has value '%s', which resides at %p\n", (void *)&hello, hello, hello);
  printf(" buf @ %p has value '%s', which resides at %p\n", (void *)&buf, buf, buf);

  // malloc allocates space on the heap
  hello = (char *)malloc(10);
  strcpy(hello, "new stuff");
  printf(" now hello @ %p has value '%s', which resides at %p\n", (void *)&hello, hello, hello);
  // free lets the heap re-use that space
  free(hello);
  printf(" note hello @ %p still points to %p\n", (void *)&hello, hello);
  
  return 0;
}
