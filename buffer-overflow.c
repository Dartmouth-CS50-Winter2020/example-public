/*
 * File:  buffer-overflow.c
 * Description: This is a bad program! But its fun. The basic idea of
              of the program to input and manipulate strings using
              arrays of chars is fun. However, there is a serious flaw in the program. 
              The book uses the function gets(). This is a seriously dangerous function call. 
              DONT USE IT. Revised code taken from pg. 457 (Program 9.5) (Bronson) "First Book on ANSI C"
 */

#include  <stdio.h>
#include <string.h> /* required for the string function library */

#define MAXELS 50

int main()
{
  char string1[MAXELS] = "Hello";
  char string2[MAXELS] = "Hello there";
  int n;

  n = strcmp(string1, string2);

  if (n < 0)
    printf("%s is less than - %s\n\n", string1, string2);
  else if (n == 0)
    printf("%s is equal to - %s\n\n", string1, string2);
  else
    printf("%s is greater than -  %s\n\n", string1, string2);

  printf("The length of string1 is %ld characters\n", strlen(string1));
  printf("The length of string2 is %ld characters\n\n", strlen(string2));

  strcat(string1," there World!");

  printf("After concatenation, string1 contains the string value\n");
  printf("%s\n", string1);
  printf("The length of this string is %ld characters\n\n",
                                                   strlen(string1));

  printf("Please enter a line of text for string2, max %ld characters: ", sizeof(string2));

  /* In the code below comment and uncomment the gets() code */
  gets(string2);

  /* In the code below comment and uncomment the fgets() code segment */

  // fgets(string2, sizeof(string2), stdin); 

  printf ("Thanks for entering %s\n", string2);
 
  /* Warning: The gets() function cannot be used securely. Because of its lack of 
  bounds checking, and the inability for the calling program to reliably determine 
  the length of the next incoming line, the use of this function enables 
  malicious users to arbitrarily change a  running program's functionality 
  through a buffer overflow attack. It is strongly suggested that the fgets() 
  function be used in all cases. OK lets type in more that 50 chars and see
  what happens - segfault!*/ 

  strcpy(string1, string2);

  printf("After copying string2 to string1");
  printf(" the string value in string1 is:\n");
  printf("%s\n", string1);
  printf("The length of string1 is %ld characters\n\n",             
	 strlen(string1));
  printf("\nThe starting address of the string1 string is: %p\n",
	 (void*) string1);
  printf("\nThe starting address of the string2 string is: %p\n",
	 (void*) string2);
  
  return 0;
}






