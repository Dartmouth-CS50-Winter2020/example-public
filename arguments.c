#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;

  printf("%d items were input on the command line\n", argc);
  for (i = 0; i < argc; i++) 
    printf("arguments %d is %s\n", i, argv[i]);

  return 0;
} 
