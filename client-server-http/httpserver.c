/* 
 * httpserver - an example HTTP server.
 *
 * This program accepts connections forever in an infinite loop.
 * It accepts and services very simple http requests.
 *
 * usage: httpserver
 *  and ctrl-C to exit.
 *
 * David Kotz - May 2016, May 2017
 * Temi Prioleau, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	      // bool type
#include <unistd.h>	      // read, write, close
#include <strings.h>	      // bcopy, bzero
#include <arpa/inet.h>	      // socket-related calls
#include "file.h"

/**************** external functions ****************/
// for some reason, when compiling with -c11 I need to declare this function.
extern FILE *fdopen(int fd, const char *mode);

/**************** file-local constants and functions ****************/
static const int LISTEN_BACKLOG = 5; // number of connections to keep waiting
static const int BUFSIZE = 1024;     // read/write buffer size

static int  start_server(void);
static void handle_client(FILE *comm_fp);

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  // no arguments to parse

  int list_sock = start_server();
  
  // Accept connections, and allow one connection at a time
  while (true) {
    // accept connection and receive communication socket (file descriptor)
    int comm_sock = accept(list_sock, 0, 0);
    if (comm_sock == -1) {
      perror("accept");
    } else {
      printf("Connection started\n");

      // to make it easier to work with, switch to stdio
      FILE *comm_fp = fdopen(comm_sock, "r+");
      if (comm_fp != NULL) {
	// correspond with the client
	handle_client(comm_fp);
	fclose(comm_fp); // implicitly calls close(comm_sock);
      } else {
	close(comm_sock);
      }

      printf("Connection ended\n");
    }
  }

  /* Note the server never explicitly exits, or closes list_sock,
   * but the socket will be closed when the program is killed or 
   * terminates. */
}

/**************** start_server ****************/
static int
start_server(void)
{
  // Create socket on which to listen (file descriptor)
  int list_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (list_sock < 0) {
    perror("opening socket stream");
    exit(1);
  }

  // Name socket using wildcards
  struct sockaddr_in server;  // server address
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;
  if (bind(list_sock, (struct sockaddr *) &server, sizeof(server))) {
    perror("binding socket name");
    exit(2);
  }

  // Print our assigned port number
  socklen_t serverlen = sizeof(server);	// length of the server address
  if (getsockname(list_sock, (struct sockaddr *) &server, &serverlen)) {
    perror("getting socket name");
    exit(3);
  }

  // prepare to accept connections
  listen(list_sock, LISTEN_BACKLOG);

  printf("Listening at port %d\n", ntohs(server.sin_port));
  printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");

  return list_sock;
}

/**************** handle_client ****************/
static void
handle_client(FILE *comm_fp)
{
  // try to read the command line
  char *httpcommand = readlinep(comm_fp);
  if (httpcommand == NULL) {
    printf("Bad http commands\n");
    fprintf(comm_fp, "HTTP/1.1 400 Bad Request\n");
    fprintf(comm_fp, "Server: CS50/1.0 (Kotz)\n");
    fprintf(comm_fp, "Connection: close\n");
    fprintf(comm_fp, "\n");
    return;
  }

  // parse the command to get the filename
  char filename[BUFSIZE];
  if (strlen(httpcommand) > BUFSIZE ||
      sscanf(httpcommand, "GET /%s HTTP/1.1\n", filename) != 1) {
    printf("Bad http command: %s\n", httpcommand);
    fprintf(comm_fp, "HTTP/1.1 400 Bad Request\n");
    fprintf(comm_fp, "Server: CS50/1.0 (Kotz)\n");
    fprintf(comm_fp, "Connection: close\n");
    fprintf(comm_fp, "\n");
    free(httpcommand);
    return;
  } else {
    free(httpcommand);
  }

  // skip until we see a blank line
  char *httpblank = NULL;
  while ( (httpblank = readlinep(comm_fp)) != NULL
	  && *httpblank != '\0'  && *httpblank != '\r') {
    free(httpblank);
  }

  if (httpblank == NULL) {
    return; // never found a blank line
  } else {
    free(httpblank);
  }
	
  FILE *file_fp = fopen(filename, "r");
  if (file_fp == NULL) {
    printf("Cannot open file: %s\n", filename);
    fprintf(comm_fp, "HTTP/1.1 404 Not Found\n");
    fprintf(comm_fp, "Server: CS50/1.0 (Kotz)\n");
    fprintf(comm_fp, "Connection: close\n");
    fprintf(comm_fp, "\n");
  } else {
    // success! copy the file to the socket
    printf("Copying file: %s\n", filename);
    fprintf(comm_fp, "HTTP/1.1 200 OK\n");
    fprintf(comm_fp, "Server: CS50/1.0 (Kotz)\n");
    fprintf(comm_fp, "Connection: close\n");
    fprintf(comm_fp, "Content-Type: text/plain; charset=UTF-8\n");
    fprintf(comm_fp, "\n");
    char c;
    while ( (c = fgetc(file_fp)) != EOF) {
      fputc(c, comm_fp);
    }
    fclose(file_fp);
  }
}
