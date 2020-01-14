/*

  File: scope.c

  Description: Illustrates the use of global and local variables and 
               global function prototypes.


   Revised code taken from pg. 330 (Program 7.1) (Bronson) "First Book on ANSI C"

*/ 

#include <stdio.h>

/* firstnum is a global variable not defined on the main() stack. It has full scope
   of all functions in the file scope.c. Any code in the file can read and write to it.
   Once main() teriminates the variable is dellocated and no longer exists 
*/

int firstnum; /* create a global variable named firstnum */

void valfun(); /* global function prototype */


int main()
{
  int secnum; /* create a local variable named secnum */
  firstnum = 10; /* store a value into the global variable */
  secnum = 20; /* store a value into the local variable */

  printf("\nFrom main(): firstnum = %d",firstnum);
  printf("\nFrom main(): secnum = %d\n",secnum);

  valfun(); /* call the function valfun */

  printf("\nFrom main() again: firstnum = %d",firstnum);
  printf("\nFrom main() again: secnum = %d\n",secnum);

  return 0;
}


void valfun() /* no values are passed to this function */
{

  /* secum is a local variable created on the stack when valfun() executes.
     When valfun() exits the stack is deallocated and the variable no
     longer exists. It is local and its scope is valfun() */

  int secnum; /* create a second local variable named secnum */
  secnum = 30; /* this only affects this local variable's value */
 

  printf("\nFrom valfun(): firstnum = %d",firstnum);
  printf("\nFrom valfun(): secnum = %d\n",secnum);
  firstnum = 40; /* this changes firstnum for both functions */

}
