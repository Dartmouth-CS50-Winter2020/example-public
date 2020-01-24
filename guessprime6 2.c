/* 
 * guessprime6.c - a C version of our bash demo program
 *  (support command-line arguments)
 * usage: guessprime [maxPrime]
 * 
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// function prototype *declarations*
int pickPrime(const int max);
int readGuess(const int max);
bool isPrime(const int p);

// Main loop - ask for a guess, quit when it matches the answer
int main(const int argc, const char *argv[]) {
  int answer; // the secret prime to guess
  int guess;  // the user's guess
  int max;    // we'll pick a prime in [1..max]

  // interpret arguments
  if (argc == 1) {
    // no arguments (other than the command) - use default value
    max = 100;
  } else if (argc == 2) {
    // one argument - should be the maxPrime
    if (sscanf(argv[1], "%d", &max) < 1 || max < 2 || max > 100) {
      printf("usage: %s [maxPrime]; your maxPrime is out of range\n", argv[0]);
      exit(1);
    }
  } else {
    // too many arguments
    printf("usage: %s [maxPrime]\n", argv[0]);
    exit(2);
  }

  answer = pickPrime(max);

  guess = readGuess(max);
  while (guess != 0 && guess != answer) {
    printf("Wrong! try again\n");
    guess = readGuess(max);
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
int readGuess(const int max) {
  int guess;

  printf("Enter a prime between 1-%d (give up? enter 0): ", max);
  scanf("%d", &guess);
  if (guess == 0) {
    return 0;
  }

  if (guess < 1 || guess > max) {
    printf("Hey! %d is out of range [1..%d].\n", guess, max);
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
