/* File: random.c
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// This function will run concurrently.
void* print_i(void *ptr) 
{
    printf("a\n");
    printf("b\n");
    return 0;
}

int main() 
{
  pthread_t t1;

  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  if (iret1) 
  {
	fprintf(stderr, "thread creation failed, rc=%d.\n", iret1);
	return (iret1);
  } 
  printf("c\n");

  return 0;
}
