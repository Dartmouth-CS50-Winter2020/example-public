/* 
 * inserver - an example Internet server.
 *
 * This program accepts connections forever in an infinite loop.
 * It receives a string from the client, then chops the string
 * into words, and prints one word at a line. Here a word is defined
 * as consecutive letters separated by non-letter character(s). 
 * 
 * usage: inserver
 *  and ctrl-C to exit.
 *
 * David Kotz, 1987, 1992, 2016
 * Adapted from Figure 7b in Introductory 4.3bsd IPC, PS1:7-16,17.
 *
 * updated by Xia Zhou, August 2016, 2017, 2018
 * updated by Temi Prioleau, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        // bool type
#include <string.h>         // memcpy, memset
#include <unistd.h>         // read, write, close
#include <arpa/inet.h>      // socket-related calls
#include <ctype.h>          // isalpha() 

/**************** file-local constants ****************/
#define SERV_PORT 3000    // server port number 
#define LISTEN_BACKLOG 5  // number of connections to keep waiting
#define BUFSIZE 1024      // read/write buffer size

/******* function prototype *************/
void sep_words(char *input); 

/**************** main() ****************/
int main(const int argc, char *argv[])
{
  int list_sock, comm_sock;
  struct sockaddr_in server;  // server address
  char buf[BUFSIZE];    // buffer for reading data from socket
  int bytes_read;       // #bytes read from socket

  // 1. Create socket on which to listen (file descriptor)
  list_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (list_sock < 0) {
    perror("opening socket stream");
    exit(1);
  }

  // 2. Initiate the fields of the server address
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERV_PORT);

  // 3. bind the socket to the given server address
  if (bind(list_sock, (struct sockaddr *) &server, sizeof(server))) {
    perror("binding socket name");
    exit(2);
  }
  printf("Listening at port %d\n", ntohs(server.sin_port));
  printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");
  
  // 4. Start accepting connections, and allow one connection at a time
  listen(list_sock, LISTEN_BACKLOG);
  while (true) {
    // accept connection and receive communication socket (file descriptor)
    comm_sock = accept(list_sock, 0, 0);
    if (comm_sock == -1)
      perror("accept");
    else {
      printf("Connection started\n");
      
      do {
        memset(buf, 0, sizeof(buf)); // fill buffer with nulls
      	if ((bytes_read = read(comm_sock, buf, BUFSIZE-1)) < 0)
      	  perror("reading stream message");
      	if (bytes_read == 0) 
      	  printf("Ending connection\n");
      	else {
      	  printf("\t%s", buf);
          sep_words(buf);  // chop the buf into words and print them
        }
      } while (bytes_read != 0);
      
      close(comm_sock);
       
      printf("Connection ended\n");
    }
  }
  
  close(list_sock);
  /* Note that if the server doesn't explicitly exit or close the socket,
   * the socket will be closed when the program is killed or terminates. */    
}


// separate an input string into words
void sep_words(char* input)
{
  char** words; // array of char* 

  // max # of pointers is the max # of words
  words = calloc(strlen(input)/2+1, sizeof(char*));

  // TODO: add your code here to split words... 

  // print one word per line
  for (int j = 0; j < i; j++) {
    printf("%s\n", words[j]);
  }

  free(words); 
}

