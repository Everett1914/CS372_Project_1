/*******************************************************************************
* Developer:  Everett Williams
* Last Modified:  101441FEB19 (Day/Time/Month/Year)
* Program Name: chatclient.c
* Assignment:  CS372 Project 1
* Description:  Client implementation for a simple chat system using a TCP.
* This program represents the client side coding.
* client server architecture.
* References:
*   https://beej.us/guide/bgnet/
*   https://beej.us/guide/bgnet/html/multi/advanced.html#sendall
*   https://medium.com/@yashitmaheshwary/simple-chat-server-using-sockets-in-c-f72fc8b5b24e
*   https://docs.python.org/2.7/library/socket.html?highlight=socket%20shutdown%20arguments
*   https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXHANDLESIZE 11 // max number of bytes we can store in the handle to include /0
#define MAXMSGSIZE 501 // max number of bytes used in messages between host to include /0

/*******************************************************************************
* int createConnection(struct addrinfo * result)
* Creates a socket and connection to the server.
* Args: The address info linked list
* Return: The socket file descriptor
*******************************************************************************/
int createConnection(struct addrinfo * result){
	int sockfd;

  //Create the socket, if error creating socket exit
	if ((sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1){
		perror("Socket Creation Error: ");
	}

  //Create the connection, if error creating connection exit
  if (connect(sockfd, result->ai_addr, result->ai_addrlen) == -1) {
    close(sockfd);
    perror("Connection Creation Error: ");
  }

	return sockfd;
}

/*******************************************************************************
* void establishConnection(int sockfd, char *serverHandle, char *username)
* Establish initial connection to server and exchanges handles.
* Args: The socket file descriptor, serverHandle, clientHandle(username)
* Return: Nothing
*******************************************************************************/
void establishConnection(int sockfd, char *serverHandle, char *username){
  int numbytes;
  if ((numbytes = send(sockfd, username, strlen(username), 0)) == -1) {
      perror("send: ");
      exit(1);
  }
  if ((numbytes = recv(sockfd, serverHandle, MAXHANDLESIZE - 1, 0)) == -1) {
      perror("recv: ");
      exit(1);
  }
  serverHandle[numbytes] = '\0';  //append null terminator to end of whatever string is sent by server.  Assume server sends no more than 10 characters w/o /0.
  printf("Creating a connection with %s\n", serverHandle);
}

void chatControl(int sockfd, char *serverHandle, char *username){
  while (1){
    int numbytes, len;
    char msgSent[MAXMSGSIZE + MAXHANDLESIZE + 2];  //handle/msg string size with max size of prepended with 1 and an arrow space between both.
    char msgRecv[MAXMSGSIZE + MAXHANDLESIZE + 2];  //handle/msg string size with max size of prepended with 1 and an arrow between both.
    char uName[MAXHANDLESIZE];
    char message[MAXMSGSIZE];

    memset(message,0,sizeof(message));
    memset(uName,0,sizeof(uName));
    memset(msgSent,0,sizeof(msgSent));
    memset(msgRecv,0,sizeof(msgRecv));

    //Get message
    printf("%s> ", username);
    fgets(message, 501, stdin);

    //Prepend username and message
    strcpy(msgSent, username);
    msgSent[strlen(msgSent)] = '>';
    msgSent[strlen(msgSent)] = ' ';
    strcat(msgSent, message);

    if(strcmp(message, "\\quit\n") == 0){
        close(sockfd);
        break;
    }

    if ((numbytes = send(sockfd, msgSent, strlen(msgSent), 0)) == -1) {
        perror("send: ");
        exit(1);
    }

    //Manage recv and shutdown if socket closed by host https://beej.us/guide/bgnet/html/multi/recvman.html
    numbytes = recv(sockfd, msgRecv, MAXMSGSIZE + MAXHANDLESIZE + 2, 0);
    if (numbytes == -1) {
        perror("recv: ");
        exit(1);
    }
    else if(numbytes == 0 || strcmp(msgRecv,"\\quit") == 0){
        printf("%s closed the connection\n", serverHandle);
        break;
    }
    else{
        msgRecv[numbytes] = '\0';
        printf("%s\n", msgRecv);
    }
  }
  close(sockfd);
}

int main(int argc, char *argv[]){
  int rv, sockfd;
  char username[MAXHANDLESIZE], serverHandle[MAXHANDLESIZE];  //username for the clientSocket
  struct addrinfo hints, *result;

  if(argc != 3){  //Throw error if incorrect number of arguments
    fprintf(stderr, "Arguement count is incorrect.  Must enter two additional arguements <hostname> <portnumber>\n");
    exit(1);
  }

  //Collect user handle
  printf("Please enter a 10 character user handle: ");
  fgets(username, 11, stdin);
  int len = strlen(username);
  if (len > 0 && username[len-1] == '\n'){
      username[--len] = '\0';
  }

  //create pointer (result) to linked list containing address info
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;  //Use IPv4
  hints.ai_socktype = SOCK_STREAM;
  if ((rv = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
  }

  //create connection
  sockfd = createConnection(result);
  establishConnection(sockfd, serverHandle, username);
  chatControl(sockfd, serverHandle, username);

  return 0;
}
