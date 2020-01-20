/* 
 * strings.c - demonstrate C strings
 *
 * This code uses gets() and thus triggers warnings when compiled on Linux.
 * The standard include files don't even define gets() any more.
 * 
 * CS 50, January 2020.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void xbuf(char *buf, const int buflen);
bool readline(char *buf, const int buflen);

// main: demonstrate some behavior of C strings
int main() {
  int buflen = 16;
  char buf1[buflen];
  char buf2[buflen];

  printf("memory locations:\n");
  printf("buflen @ %p, %ld bytes\n", (void*) &buflen, sizeof(buflen));
  printf("buf1 @ %p, %ld bytes\n", (void*) buf1, sizeof(buf1));
  printf("buf2 @ %p, %ld bytes\n", (void*) buf2, sizeof(buf2));
  printf("buf1-buf2=%ld; buflen-buf1=%ld\n", buf1-buf2, (char*)&buflen-(char*)buf1);
  
  printf("String constant '%s'\n", "this is a string constant");

  // assign a constant to each buffer
  strcpy(buf1, "hello");  // like buf1 = "hello"
  strcpy(buf2, "world!");  // like buf2 = "world!"

  printf("buf1='%s', buf2='%s'\n", buf1, buf2);

  printf("buf1='%s', length %ld\n", buf1, strlen(buf1));
  for (int i=0; buf1[i] != '\0'; i++)
    printf("buf1[%d] = %c\n", i, buf1[i]);
    
  // copy buf1 into buf2 (note argument order)
  strcpy(buf2, buf1); // like buf2 = buf1
  printf("buf1='%s', buf2='%s'\n", buf1, buf2);

  // compare buf1 and buf2;
  // returns negative if buf1<buf2, zero if equal, positive if buf1>buf2
  if (strcmp(buf1, buf2) == 0)
    printf("buf1==buf2\n");
  else
    printf("buf1!=buf2\n");
    
  // concatenate buf2 on to end of buf1
  strcat(buf1, buf2); // like buf1 = buf1 + buf2
  printf("buf1='%s', buf2='%s'\n", buf1, buf2);

  // try to copy buf2 into buf1
  strcpy(buf1, "");			 // like buf1 = ""
  strcpy(buf2, "");			 // like buf2 = ""
  strcpy(buf2, "A 21-character string"); // like buf2 = "a 21-character string"
  printf("buf1='%s', buf2='%s'\n", buf1, buf2); // look at the output carefully!

  // fill each buf with x's and terminate each with null character
  xbuf(buf1, buflen);
  xbuf(buf2, buflen);
  printf("buf1='%s', buf2='%s'\n", buf1, buf2);
  
  // try again, with strncpy
  strncpy(buf2, "A 21-character string", buflen-1); // copy at most buflen-1 chars
  printf("buf1='%s', buf2='%s'\n", buf1, buf2); // now look at the output!

  // fill each buf with x's
  xbuf(buf1, buflen);
  xbuf(buf2, buflen);
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);
  
  // read a line from stdin, into buf2
  printf("enter a short string: ");
  gets(buf2); // UNSAFE
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);

  // fill each buf with x's
  xbuf(buf1, buflen);
  xbuf(buf2, buflen);
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);
  
  // read a line from stdin, into buf2
  printf("enter a longer string: ");
  gets(buf2); // UNSAFE
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);
  
  // fill each buf with x's
  xbuf(buf1, buflen);
  xbuf(buf2, buflen);
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);

  // read again, safely
  printf("enter another long string: ");
  readline(buf2, buflen);
  printf("buf1='%s', buf2='%s', buflen=%d\n", buf1, buf2, buflen);
}

// fill the buf with x's and terminate with null character
void xbuf(char *buf, const int buflen) {
  for (int i = 0; i < buflen; i++)
    buf[i] = 'x';
  buf[buflen-1] = '\0';
}


// Safely read a line of input into the given `buf` (with room for `len` chars);
// guaranteeing we won't over-run the end of the buffer,
// guaranteeing a newline-terminated, null-terminated string in the buffer;
// returning true if success and false if EOF or any error.
// If the user enters more than len-2 characters, that is considered an error.
// If end-of-file is reached before newline, that is considered an error.
bool readline(char *buf, const int len) {
  // if fgets encounters an error, or EOF after no input, it returns NULL.
  if (fgets(buf, len, stdin) == NULL)
    return false;

  // this should not happen, but I want to protect the subscript below
  if (strlen(buf) == 0)
    return false;
  
  // fgets guarantees the string is null-terminated, but there may not be a
  // newline if the buffer filled before a newline was encountered.
  // if that happens, clear the stdio input until newline or EOF.
  if (buf[strlen(buf)-1] != '\n') {
    // strip characters until end of file or newline is reached
    while ( !feof(stdin) && getchar() != '\n' )
      ; // discard the rest of characters on input line
    return false;
  }

  return true;
}
