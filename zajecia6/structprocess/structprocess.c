#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define SIZE 80

typedef struct
{
  int type; // Typ komunikatu
  char text[SIZE]; // Tekst komunikatu
} msg_tp;

int main(int argc, char *argv[])
{
  int i;
  int res, status;
  char text[100];
  unsigned int prio = 10;
  mqd_t mq;
  msg_tp msg;
  struct mq_attr attr;
  // Ustalenie atrybutów kolejki ----------------
  attr.mq_msgsize = sizeof (msg);
  attr.mq_maxmsg = 4;
  // Utworzenie kolejki komunikatow ------------
  mq = mq_open("/MQ22", O_RDWR | O_CREAT, 0666, &attr);
  if (mq < 0) { // Błąd
    perror("Kolejka MQ1");
    exit(-1);
  }
  if (fork() == 0)
    {
      for (i = 0; i < 10; i++)
	{
	  //sprintf(msg.text, "Proces 2 komunikat %d", i);
	  // Odbiór komunikatu ----------------
	  res = mq_receive(mq, (text), sizeof (text), &prio);
	  printf("%s\n", text);
	  fflush(stdout);
	  sleep(1);
	}
      printf("koniec\n");
    } else {
    for (i = 0; i < 10; i++)
      {
	sprintf(msg.text, "Proces 1 komunikat %d", i);
	printf("wysylam %s\n", msg.text);
	fflush(stdout);
	// Wysłanie komunikatu ----------------
	res = mq_send(mq, msg.text, sizeof (msg.text), 10);
	sleep(1);
      }
  }
  wait(&status);
  mq_close(mq);
  mq_unlink("/MQ22");
  return EXIT_SUCCESS;
}
