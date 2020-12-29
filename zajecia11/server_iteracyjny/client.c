#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#define BUFLEN 1024
#define NUM_THREADS 5

//CLIENT
void *loop(void *arg) 
{
  struct sockaddr_in server;
  unsigned char localhost[] = {127, 0, 0, 1};
  char buf[BUFLEN];
  int sock, n, tid;
  tid = *(int*) arg;
  printf("Watek %d wystartowal\n", tid);
  for(;;) 
    {
      sock = socket(AF_INET, SOCK_STREAM, 0);
      memset(&server, 0, sizeof (server));
      server.sin_family = AF_INET;
      memcpy(&server.sin_addr, localhost, 4);
      server.sin_port = htons(10000);
      if (connect(sock, (struct sockaddr *) &server, sizeof (server)))
	{
	  printf("Watek %d, polaczenie nieudane - ""praca wstrzymana na 10 sekund\n", tid);
	  close(sock);
	  sleep(10);
	  continue;
        }
      n = read(sock, buf, BUFLEN - 1);
      if (n > 0) {
	buf[n] = 0;
	printf("Watek %d przeczytal %d bajtow, wartosc: %s", tid, n, buf);
      }
      close(sock);
    }
}
int main(int argc, char** argv)
{
  int x;
  pthread_t tid;
  for (x = 0; x < NUM_THREADS; x++)
    pthread_create(&tid, NULL, loop, &x);
  int n = 0;
  for (;;)
    {
      printf("[%d]\n", n++);
      sleep(1);
    }
  return (EXIT_SUCCESS);
}
