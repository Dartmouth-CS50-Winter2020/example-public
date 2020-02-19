/* 
 * inclient - an example Internet client.
 *
 * Makes a connection to the given host/port and sends a message 
 * to that socket.
 * 
 * usage: inclient hostname port
 * 
 * David Kotz, 1987, 1992, 2016
 * Adapted from Figure 7a in Introductory 4.3bsd IPC, PS1:7-15.
 *
 * updated by Xia Zhou, August 2016, 2017, 2018
 * updated by Temi Prioleau, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	      // read, write, close
#include <string.h>	      // memcpy, memset
#include <netdb.h>	      // socket-related structures

/**************** file-local constants ****************/
#define BUFSIZE 1024     // read/write buffer size

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  char *program;	  // this program's name
  char *hostname;	  // server hostname
  int port;		      // server port

  // 0. Check arguments
  program = argv[0];
  if (argc != 3) {
    fprintf(stderr, "usage: %s hostname port\n", program);
    exit(1);
  } else {
    hostname = argv[1];
    port = atoi(argv[2]);
  }

  // 1. Create socket
  int comm_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (comm_sock < 0) {
    perror("opening socket");
    exit(2);
  }

  // 2. Initialize the fields of the server address
  struct sockaddr_in server;  // address of the server
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  // Look up the hostname specified on command line
  struct hostent *hostp = gethostbyname(hostname); // server hostname
  if (hostp == NULL) {
    fprintf(stderr, "%s: unknown host '%s'\n", program, hostname);
    exit(3);
  }  
  memcpy(&server.sin_addr, hostp->h_addr_list[0], hostp->h_length);

  // 3. Connect the socket to that server   
  if (connect(comm_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("connecting stream socket");
    exit(4);
  }
  printf("Connected!\n");

  // 4. Read content from stdin (file descriptor = 0) and write to socket
  char buf[BUFSIZE];    // a buffer for reading data from stdin
  int bytes_read;       // #bytes read from socket
  memset(buf, 0, BUFSIZE); // clear up the buffer
  do {
    if ((bytes_read = read(0, buf, BUFSIZE-1)) < 0) {
      perror("reading from stdin");
      exit(5);
    } else {
      if (write(comm_sock, buf, bytes_read) < 0)  {
      	perror("writing on stream socket");
      	exit(6);
      }
    }
  } while (bytes_read > 0);
  
  close(comm_sock);

  return 0;
}
