/* 
 * httpclient - an example HTTP client.
 *
 * Makes a connection to the given host/port and issue GET for the given file.
 * 
 * usage: httpclient hostname port filename
 * 
 * David Kotz - May 2016, May 2017
 * Temi Prioleau, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	      // read, write, close
#include <strings.h>	      // bcopy, bzero
#include <netdb.h>	      // socket-related structures
#include "file.h"	      // readfilep

/**************** external functions ****************/
// for some reason, when compiling with -c11 I need to declare this function.
extern FILE *fdopen(int fd, const char *mode);

/**************** file-local constants and functions ****************/
static void parse_args(const int argc, char *argv[], 
		       char **program, char **hostname, 
		       int *port, char **filename);
static FILE *connect_to(const char *hostname, const int port);

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  char *program;	      // this program's name
  char *hostname;	      // server hostname
  int port;		      // server port
  char *filename;	      // filename to get

  // parse arguments - exit on error
  parse_args(argc, argv, &program, &hostname, &port, &filename);

  // open connection - exit on error
  FILE *comm_fp = connect_to(hostname, port);

  // prepare and send HTTP request
  const char *httpformat = "GET %s HTTP/1.1\nHOST: %s\n\n";
  if (fprintf(comm_fp, httpformat, filename, hostname) < 0) {
    perror("writing on stream socket");
    exit(6);
  }
  // ensure stdio buffer is flushed to socket
  fflush(comm_fp);

  // read and print the server's response
  char *response = readfilep(comm_fp);
  if (response != NULL) {
    puts(response);
    free(response);
  }
  fclose(comm_fp);    // implicitly calls close(comm_sock);
  
  return 0;
}

/* ********************************************************* */
static void 
parse_args(const int argc, char *argv[], 
		       char **program, char **hostname, 
		       int *port, char **filename)
{
  // check arguments
  *program = argv[0];
  if (argc != 4) {
    fprintf(stderr, "usage: %s hostname port filename\n", *program);
    exit(1);
  } else {
    // we really should check the args more carefully.
    *hostname = argv[1];
    *port = atoi(argv[2]);
    *filename = argv[3];
  }
}

/* ********************************************************* */
static FILE *
connect_to(const char *hostname, const int port)
{
  // Look up the hostname specified on command line
  struct hostent *hostp = gethostbyname(hostname);
  if (hostp == NULL) {
    fprintf(stderr, "unknown host '%s'\n", hostname);
    exit(3);
  }

  // Initialize fields of the server address
  struct sockaddr_in server;  // address of the server
  server.sin_family = AF_INET;
  bcopy(hostp->h_addr_list[0], &server.sin_addr, hostp->h_length);
  server.sin_port = htons(port);

  // Create socket (a file descriptor)
  int comm_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (comm_sock < 0) {
    perror("opening socket");
    exit(2);
  }

  // And connect that socket to that server   
  if (connect(comm_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("connecting stream socket");
    exit(3);
  }

  // to make it easier to work with, switch to stdio
  FILE *comm_fp = fdopen(comm_sock, "r+");
  if (comm_fp == NULL) {
    fprintf(stderr, "error converting socket to FILE*\n");
    exit(4);
  }

  return comm_fp;
}
