/* 
 * readline.c - a utility function to safely read one line of input
 * See readline.h for documentation.
 *
 * CS50, Jan 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "readline.h"

bool readline(char *buf, const int len) 
{
  int pos = 0;		      // where in the buffer do we place next char?

  // fill the buffer from stdin until buf is full, until EOF, or until newline
  while ( !feof(stdin) && pos < len-1 ) {
    // read and store a character
    char c = getchar();
    buf[pos++] = c;

    if (c == '\n') {
      // end of line: terminate buf and return
      buf[pos++] = '\0';
      return true;
    }
  }
  // terminate buffer
  buf[pos++] = '\0';

  // error: file ended or buffer filled before newline discovered.

  // strip characters until end of file or newline is finally reached
  while ( !feof(stdin) && getchar() != '\n' ) {
    ; // discard the rest of characters on input line
  }

  return false;
}
