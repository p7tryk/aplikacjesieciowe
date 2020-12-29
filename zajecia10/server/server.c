#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFLEN 1000

int main()
{

  
  struct sockaddr_in server;

  char buffer[BUFLEN];
  
  int sock,csock, n;
  

  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock<0)
    return 0;

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  if(bind(sock, (struct sockaddr * ) &server,sizeof(server)))
    {
      perror("bind");
      exit(1);
    }
  
  listen(sock, 5);
  for(;;)
    {
      csock = accept(sock, NULL, NULL);
      printf("klient podłaczony");
      while((n = read(csock, buffer, BUFLEN - 1)) > 0 )
	{
	  buffer[n] = '\0';
	  printf("przeczytane bajty %d: %s", n, buffer);
	}
      
    }

}
