/* 
 * guessprime5.c - a C version of our bash demo program
 *  (pick a random answer)
 *
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// function prototype *declarations*
int pickPrime(const int max);
int readGuess(void);
bool isPrime(const int p);

// Main loop - ask for a guess, quit when it matches the answer
int main() {
  const int answer = pickPrime(100);
  int guess;

  guess = readGuess();
  while (guess != 0 && guess != answer) {
    printf("Wrong! try again\n");
    guess = readGuess();
  }

  if (guess == 0) {
    printf("Hah! you gave up; the answer was %d\n", answer);
  }
  if (guess == answer) {
    printf("You win!\n");
  }

  return 0;  // exit status
}

// pick a random prime between 1..max
int pickPrime(const int max) {
  int p;

  srand(time(NULL)); // seed the random-number sequence

  // keep picking random numbers until we find a prime
  for (p = 0; !isPrime(p); p = (rand() % max + 1))
    ;

  return p;
}

// Prompt for, and read, one guess
// return 0 if they gave up
int readGuess(void) {
  int guess;

  printf("Enter a prime between 1-100 (give up? enter 0): ");
  scanf("%d", &guess);

  if (guess == 0) {
    return 0;
  }

  if (guess < 1 || guess > 100) {
    printf("Hey! %d is out of range [1..100].\n", guess);
  }
    
  if (!isPrime(guess)) {
    printf("Hey! %d is not even a prime number.\n", guess);
  }

  return guess;
}


// determine whether the number is prime
// (assumes n <= 100)
bool isPrime(const int n) {
  if (n < 2) return false;
  if (n > 2 && n%2 == 0) return false;
  if (n > 3 && n%3 == 0) return false;
  if (n > 5 && n%5 == 0) return false;
  if (n > 7 && n%7 == 0) return false;
  return true;
}
