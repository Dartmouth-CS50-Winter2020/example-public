/* 
 * guessprime.c - a C version of our simple bash demo program guessprime.sh
 *  (add listPrimes() function)
 *
 * Input: a guessed integer 
 * Output: whether the guess matches the answer, if so, print out all primes 
 *         within [1, 100], otherwise, keep asking guesses
 *
 * CS50, January 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function prototype *declarations*
int readGuess(void);
bool isPrime(const int p);
void listPrimes(const int min, const int max);

// Main function - ask for a guess, quit if it matches the answer and keep asking otherwise
int main() {
  const int answer = 31;
  int guess;

  guess = readGuess();
  while (guess != answer) {
    // print msg only if it's a valid guess 
    if (guess > 0) printf("Wrong! try again\n"); 
    guess = readGuess();
  }

  printf("Hey you win! Here's a list of primes in [1..100]:\n");
  listPrimes(1, 100);

  return 0;  // exit status
}


// Ask for and read a guess
// function actual *definition*
int readGuess(void) {
  int guess;

  printf("Enter a prime between 1-100: ");
  if (scanf("%d", &guess) < 1) {
    printf("Hey! invalid number.\n");
    while (getchar() != '\n')
      ; // discard the rest of characters on input line 
    return -1;
  }

  if (guess < 1 || guess > 100) {
    printf("Hey! %d is out of range [1..100].\n", guess);
    return -1;
  }
    
  if (!isPrime(guess)) {
    printf("Hey! %d is not even a prime number.\n", guess);
    return -1;
  }

  return guess;
}


// Check whether the number is prime
// (assuming n <= 100)
bool isPrime(const int n) {
  if (n < 2) return false;
  if (n > 2 && n%2 == 0) return false;
  if (n > 3 && n%3 == 0) return false;
  if (n > 5 && n%5 == 0) return false;
  if (n > 7 && n%7 == 0) return false;
  return true;
}


// Print all the primes between min and max
void listPrimes(const int min, const int max) {
  for (int p=min; p <= max; p++) {
    if (isPrime(p))
      printf("%d ", p);
  }
  printf("\n");
}
