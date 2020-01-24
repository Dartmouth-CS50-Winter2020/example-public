/*

  File: operator.c

  Description: Implements basic operations (multiplication, division, addition, modulos.


  Revised version of code pg. 191 (Program 4.6) (Bronson) "First Book on ANSI C"

*/ 

#include <stdio.h>

int main() {

  int opselect;
  float fnum, snum;

  printf("Please type in two numbers: ");
  scanf("%f %f", &fnum, &snum);
  printf("Enter a select code:");
  printf("\n 1 for addition");
  printf("\n 2 for multiplication");
  printf("\n 3 for division : ");
  printf("\n 4 for modulus  : ");
 
  scanf("%d", &opselect); 

  // This line below as an intentional bug. It is commented out. 
  // it causes a segmentation fault (segfault for short)

  //scanf("%d", opselect); 

  switch (opselect) {

    case 1:
      printf("The sum of the numbers entered is %6.3f\n", fnum + snum);
      break;
    case 2:
      printf("The product of the numbers entered is %6.3f\n", fnum * snum);
      break;

    case 3:
      if (snum != 0.0)
        printf("The first number divided by the second is %6.3f\n",fnum / snum);
      else
		      printf("Division by zero is not allowed\n");
      break; 

    case 4:
      printf("The modulus of the numbers entered is %d\n", (int)fnum % (int)snum);
      break;

    default:
      printf("Need to enter a number between 1-4\n\n"); 

 }

 return 0;
}
