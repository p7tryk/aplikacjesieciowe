#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

//CLIENT
void sendcommand(char * command, int sock, int flags, char * buffer)
{
  
  printf("\nsending:\n%s", command);
  int sentbytes = send(sock, (void*) command, strlen(command), 0);
  if(sentbytes > 0)
    printf("\nwritten %d\n",sentbytes);
  else
    perror("sendto");

  sleep(1);
  for(int receivedbytes = recv(sock,buffer,BUFSIZE,flags);receivedbytes>0;receivedbytes = recv(sock, buffer, BUFSIZE,flags))
    {
      printf("\nreceived %d\n",receivedbytes);
      write(1, buffer, receivedbytes);
    }
}

int main(int argc, char** argv)
{
  int clientno = 0;
  if(argc>1)
    clientno = atoi(argv[1]);
  
  struct sockaddr_in server;
  socklen_t server_length;
  unsigned char localhost[] = IP_ADDR;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  memcpy(&server.sin_addr, localhost, 4);
  server.sin_port = htons(PORTNO);
  if (connect(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("connect");
      exit(0);
    }



  char * newmessage = malloc(sizeof(char)*BUFSIZE);
  char * buffer = malloc(sizeof(char)*BUFSIZE);

  fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK); //make it nonblock

  while(1)
    {
      for(int i = 0; i<BUFSIZE;i++)
	buffer[i] = '\0'; //cos dziwnego sie dzialo wiec lepiej wyclearowac


      printf(ANSI_COLOR_GREEN "" ANSI_BOLD "\nuselesshell$ " ANSI_COLOR_RESET);


      
      fgets(newmessage,BUFSIZE,stdin);
      if(strcmp(newmessage,"exit")==0)
	break;
      
      //newmessage[strlen(newmessage)] = EOF;
      sendcommand(newmessage,sock, 0 , buffer);
    }
  close(sock);
  free(newmessage);
  free(buffer);
  return (EXIT_SUCCESS);
}
