/* 
 * guessprime4.c - a C version of our simple bash demo program guessprime.sh
 *  (added isPrime()function)
 *
 * Input: a guessed integer 
 * Output: whether the guess matches the answer
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

// Main function - ask for a guess, quit if it matches the answer and keep asking otherwise
int main() {
  const int answer = 31;
  int guess;
  int guess_cnt;

  guess = readGuess();
  guess_cnt= 1; // keep track of the number of guesses. Set 10 to be the max.
  while (guess != answer && guess_cnt < 10) {
    printf("Wrong! try again\n");
    guess = readGuess();
    guess_cnt++;
  }

  printf("31 is the secret prime number.\n");
  return 0;  // exit status
}


// Ask for and read a guess
// function actual *definition*
int readGuess(void) {
  int guess;

  printf("Enter a prime between 1-100: ");
  scanf("%d", &guess);

  if (guess < 1 || guess > 100) {
    printf("Hey! %d is out of range [1..100].\n", guess);
  }
    
  if (!isPrime(guess)) {
    printf("Hey! %d is not even a prime number.\n", guess);
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
