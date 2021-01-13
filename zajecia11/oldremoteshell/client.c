#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define BUFSIZE 500
#define PORTNO 10022

//CLIENT
void sendcommand(char * command, int sock, int flags, struct sockaddr * server, socklen_t * clen)
{
  int x = sendto(sock, command, strlen(command),flags, server, *clen);
  printf("written %d\n",x);
  char * buffer = malloc(sizeof(char)*BUFSIZE);
  sleep(1);
  int n = recv(sock, buffer, BUFSIZE - 1, flags);
  if (n > 0)
    {
      buffer[n] = '\0';
      printf("przeczytal %d bajtow, wartosc:\n %s", n, buffer);
    }
  sleep(5);
}
void *loop(void *arg) 
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
      printf("polaczenie nieudane\n");
    }
  sendcommand("ls",sock, 0 ,(struct sockaddr*)&server,&server_length);
  return arg;
}


int main(int argc, char** argv)
{
  loop(NULL);
  return (EXIT_SUCCESS);
}
