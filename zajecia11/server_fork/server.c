#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>

struct svc_arg {
  int sock;
  int los;
};

void handler_sigcld(int sig)
{
  int status;
  while (waitpid(-1, &status, WNOHANG) > 0);
}


void *service(void *arg)
{
  char buf[100];
  struct svc_arg *a = (struct svc_arg *) arg;
  sprintf(buf, "OK %d sekund\r\n", a->los);
  sleep(a->los);
  write(a->sock, buf, strlen(buf));
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
      a.sock = accept(sock, NULL, NULL);
      a.los = 5 + rand() % 6;
      if (fork() == 0)
	{
	  close(sock);
	  service(&a);
	  close(a.sock);
	  exit(0);
        }
      close(a.sock);
    }
}
