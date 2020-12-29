#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PORTNO 10022
#define BUFSIZE 500

//SERVER

void handler_sigcld(int sig)
{
  int status;
  while (waitpid(-1, &status, WNOHANG) > 0);
}

void shell(char * command, struct sockaddr * client, socklen_t client_length)
{
  
}
void thread(void * arg)
{

}

int main(int argc, char** argv)
{
  struct sockaddr_in server;

  int sock, opt;
  signal(SIGCLD, handler_sigcld);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORTNO);
  if (bind(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("bind");
      exit(1);
    }

  listen(sock, 5);

  while(1)
    {
      int clientsocket;
      clientsocket=accept(sock,NULL, NULL);

      char * buffer = malloc(sizeof(char)*BUFSIZE);
      if(clientsocket>0)
	{
	  sprintf(buffer,"hi from server\n");
	  printf("sending to socket:\n%s",buffer);
	  send(clientsocket,buffer, strlen(buffer),0);
	  int n = recv(clientsocket,buffer, BUFSIZE, 0);
	  printf("receiving from socket:\n");
	  write(1, buffer, n);
	}
      else
	perror("accept");
  
      free(buffer);
    }
}
