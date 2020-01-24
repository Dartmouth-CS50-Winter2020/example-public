/* The program parses the input switches to sort
 * supports command lines such as `sort -r -u -n`
 * but not `sort -run` 
 */

#include <stdio.h>

int main(int argc, char *argv[]) 
{
  int unique, reverse, numsort;
  char *progname;
  
  progname = argv[0];
  numsort=reverse=unique = 0;
  
  // run through the input commands looking 
  // for switches
  while((argc > 1) && (argv[1][0] == '-')) {
    // argv[1][1] is the actual option
    switch (argv[1][1]) {
    case 'r': 
        printf("Switch is %c\n", argv[1][1]);
        reverse = 1;
        break;
    case 'u':
        printf("Switch is %c\n", argv[1][1]);
        unique = 1;
        break;
    case 'n':
        printf("Switch is %c\n", argv[1][1]);
        numsort = 1;
        break;
    default:
         printf("Error: bad option \'%c\'\n", argv[1][1]);
         printf("Usage:  %s [-r] [-u] [-n] \n", progname);
         break;
    }

    // decrement the number of arguments left
    // increment the argv pointer to the next argument
    argc--; 
    argv++;
  }
  printf( "numsort=%d, unique=%d, reverse=%d\n", numsort, unique, reverse);

  // other processing
  return 0;
}
