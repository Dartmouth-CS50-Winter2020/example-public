/* 
 * overflow.c - writing past the end of a string
 * 
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
  int buflen = 16;
  char buf1[buflen];
  char buf2[buflen];
  int example = 0;

  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  // assign a constant to each buffer
  strcpy(buf1, "hello");  // like buf1 = "hello"
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  strcpy(buf2, "class!");  // like buf2 = "class!"
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  // assign a longer constant to each buffer
  strcpy(buf1, "hellohellohello"); // 15 characters
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  strcpy(buf2, "class!class!class!");  // 18 characters
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  putchar ('\n');
  for (int i = 0; i < buflen; i++) {
    printf("buf1[%d] = '%c'\n", i, buf1[i]);
  }

  return 0;
}
