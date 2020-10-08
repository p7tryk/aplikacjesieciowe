#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int licznik1 = 1;
int licznik2 = 1;

void handler_sigint(int signal)
{
  int i = licznik1++;
  printf("sigint %d\n", i);
  fflush(stdout);
  sleep(5);
  printf("sigint koniec %d\n", i);
}

void handler_sigstop(int signal)
{
  int i = licznik2++;
  printf("sigterm %d\n", i);
  fflush(stdout);
  sleep(5);
  printf("sigterm koniec %d\n", i);
}


int main()
{
  /* sleep(10); */
  signal(SIGINT, handler_sigint);
  signal(SIGTERM, handler_sigstop);
  printf("Hello World!\n");
  int i;
  for(;;)
    {
      printf("*");
      fflush(stdout);
      sleep(1);
    }
  /* scanf("%d", &i); */
  return 0;
}
