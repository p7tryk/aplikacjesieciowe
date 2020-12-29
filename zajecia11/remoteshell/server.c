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

struct svc_arg
{
  int sock;
  struct sockaddr client;
};

void handler_sigcld(int sig)
{
  int status;
  while (waitpid(-1, &status, WNOHANG) > 0);
}

void shell(char * command)
{
  
}


void *service(void *arg)
{
  int bytes;
  char * buffer = malloc (sizeof(char)*BUFSIZE);
  struct  svc_arg * service = (struct svc_arg *) arg;

  printf("connection from %s\n",service->client.sa_data);
  
  while(1)
    {
      bytes = recv(service->sock, buffer, BUFSIZE-1,0);
      if(bytes>0)
	{
	if(fork()==0)
	  {
	    printf("fork()\n)");
	    close(1);
	    dup(service->sock);
	    printf("read %d bytes\n",bytes);
	    printf("%s",buffer);
	    exit(0);
	  }
	}
      else
	{
	  perror("read");
	  printf("read %d\n",bytes);
	  break;
	}
    }
  free(buffer);
  return arg;
}

int main(int argc, char** argv)
{
  struct sockaddr_in server;

  int sock, opt;
  struct svc_arg a;
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

  struct sockaddr client;
  
  for (;;)
    {
      a.sock = accept(sock, &client, NULL);
      memcpy(&a.client, &client, sizeof(struct sockaddr));
      if (fork() == 0)
	{
	  printf("fork()\n");
	  close(sock);
	  service(&a);
	  close(a.sock);
	  exit(0);
        }
      close(a.sock);
    }
}
