/* File: mutex.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// try uncommenting and commenting the mutext below
// and look at the output

void print(char* a, char* b) {
  pthread_mutex_lock(&mutex1); // comment out
  printf("1: %s\n", a);
  sleep(1);
  printf("2: %s\n", b);
  pthread_mutex_unlock(&mutex1); // comment out
  
}


// These two functions will run concurrently.
void* print_i(void *ptr) {
  print("I am", " in i");
  return NULL;
}

void* print_j(void *ptr) {
  print("I am", " in j");
  return NULL;
}

int main() {
  pthread_t t1, t2;
  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  int iret2 = pthread_create(&t2, NULL, print_j, NULL);

  if (iret1 || iret2) {
    fprintf(stderr,"pthread_create failed: iret1=%d, iret2=%d\n", iret1, iret2);
  }
  else {
    sleep(8);
  }
  exit(0); //never reached.
}
