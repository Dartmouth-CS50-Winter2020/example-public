/*

  file: increment.c

  Description: Illustrate pre and post increment and decrement.

*/ 

#include <stdio.h>

int main() {

     int fred = 3, a=3;

     printf("Start; fred = %d and a = %d\n", fred, a);
     a = --fred;
     printf("a = --fred; fred = %d and a = %d\n", fred, a);
     a = ++fred;
     printf("a = ++fred; fred = %d and a = %d\n", fred, a);
     a = fred--;
     printf("a = fred--; fred = %d and a = %d\n", fred, a);
     a = fred++;
     printf("a = fred++; fred = %d and a = %d\n", fred, a);

     return 0;

}
