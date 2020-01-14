#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;

  printf("\nThe number of items on the command line is %d\n\n",argc);
  for (i = 0; i < argc; i++)
  {
    printf("argument %d is \"%s\" \n", i, argv[i]);
    printf("The address stored in argv[%d] is %#08x\n", i, (unsigned int)argv[i]);
    printf("The first character pointed to there is \'%c\'\n", *argv[i]);
  }

  return 0;
}





