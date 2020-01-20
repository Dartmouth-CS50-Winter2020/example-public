/* 
 * stringcopy-fixed - fixing a naive and buggy implementation of 
 * copying strings
 *
 * CS50 January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringcopy(char *sp, char *dp);

int main()
{
  char *src = "CS 50";
  char *dest = "";  // fix 2: char dest[] = "12345";

  // copy src to dest and print them out
  dest = malloc(strlen(src)+1);
  stringcopy(src, dest);
  printf("src  = '%s'\n", src);
  printf("dest = '%s'\n", dest);
  free(dest);  // do not forget to free
  return 0;
}

/* stringcopy - copy string from source sp to destination dp */
void stringcopy(char *sp, char *dp)
{
  while (*sp != '\0') {
    *dp++ = *sp++;
  }
  *dp = '\0';
}
