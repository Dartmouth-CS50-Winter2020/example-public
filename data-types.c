/*

  file: data-types.c

  Description: Sets up variables for different base data types, intialises them
  and print the data and the size of the base data types in number of bytes.


  Revised version of code pg. 96 (Program 2.10) (Bronson) "First Book on ANSI C"

*/ 

#include <stdio.h>

int main() {

  char ch = 'a';
  int in = 2;
  short sh = 3;
  long lo = 4;
  float fl = 1000.256734;
  double db = 11e+23;
  long double ld = 10e+30;

  printf("-------contents ------- sizeof()------\n\n");

  printf("contents of char is %c --- sizeof %ld bytes\n\n", ch, sizeof(char));

  printf("contents int is  %d --- sizeof  %ld bytes\n\n", in, sizeof(int));

  printf("contents short is  %d --- sizeof %ld bytes\n\n", sh, sizeof(short));

  printf("contents long is %ld --- sizeof %ld bytes\n\n", lo, sizeof(long));

  printf("contents float is %f --- sizeof %ld bytes\n\n",fl, sizeof(float));

  printf("contents double is  %e --- sizeof %ld bytes\n\n",db, sizeof(double));

  printf("contents long double is  %LG --- sizeof %ld bytes\n",ld, sizeof(long double));
  
  return 0;

}
