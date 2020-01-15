/* 
 * freadline.c - a utility function to safely read one line of input
 * See freadline.h for documentation.
 *
 * CS50, January 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "freadline.h"

bool freadline(FILE *fp, char *buf, const int len) 
{
  int pos = 0;		      // where in the buffer do we place next char?

  // fill the buffer from fp until buf is full, until EOF, or until newline
  while ( !feof(fp) && pos < len-1 ) {
    // read and store a character
    char c = getc(fp);
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
  while ( !feof(fp) && getc(fp) != '\n' ) {
    ; // discard the rest of characters on input line
  }

  return false;
}
