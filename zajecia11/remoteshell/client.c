#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define BUFSIZE 500
#define PORTNO 10022

//CLIENT
void sendcommand(char * command, int sock, int flags, struct sockaddr * server, socklen_t * server_length)
{
  struct sockaddr_in testclient;
  socklen_t testclient_length;
  char * buffer = malloc(sizeof(char)*BUFSIZE);
  int sentbytes = sendto(sock, command, strlen(command), 0, server, *server_length);
  printf("written %d\n",sentbytes);

  int receivedbytes = recvfrom(sock, buffer, BUFSIZE,flags, (struct sockaddr *) &testclient, &testclient_length);
  printf("received %d\n",receivedbytes);
  write(1, buffer, strlen(buffer));

  
  free(buffer);
}

int main(int argc, char** argv)
{
  struct sockaddr_in server;
  socklen_t server_length;
  unsigned char localhost[] = {127, 0, 0, 1};
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
  sprintf(newmessage, "hi from client\n");
  sendcommand(newmessage,sock, 0 ,(struct sockaddr*)&server,&server_length);

  free(newmessage);
  return (EXIT_SUCCESS);
}
