/* The program parses the input switches to sort
 * supports command lines such as sort -r -u -n
 * but not sort -run 
 */

#include<stdio.h>
#include <unistd.h>
#include <getopt.h>  // how did we know to include this??? "man 3 getopt"

int main(int argc, char *argv[]) 
{
  int unique, reverse, numsort;
  char ch;
  char *progname;
  
  progname = argv[0];
  
  // run through the input commands looking 
  // for switches using the handy-dandy getopt function!
  while ((ch = getopt(argc, argv, "run")) != -1) {
    switch (ch) {
      case 'r': 
        printf("Switch is %c\n", ch);
        reverse = 1;
        break;
      case 'u':
        printf("Switch is %c\n", ch);
        unique = 1;
        break;
      case 'n':
        printf("Switch is %c\n", ch);
        numsort = 1;
        break;
      default:
        printf("Error: bad option \'%c\'\n", ch);
        printf("Usage:  %s [-r] [-u] [-n] \n", progname);
        break;
    }
  }
  printf( "numsort=%d, unique=%d, reverse=%d\n", numsort, unique, reverse);

  // other processing
  return 0;
}
