#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


//SERVER
void *service(void *arg)
{
  int n;
  char buf[100];
  n = 5 + rand() % 6;
  sprintf(buf, "OK %d sekund\r\n", n);
  sleep(n);
  write(*((int *) arg), buf, strlen(buf));
  return arg;
}

int main(int argc, char** argv)
{
  struct sockaddr_in server;
  int sock, csock, opt;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  if (bind(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("bind");
      exit(1);
    }
  listen(sock, 5);
  srand(time(NULL));
  for (;;)
    {
      csock = accept(sock, NULL, NULL);
      service(&csock);
      close(csock);
    }
}
