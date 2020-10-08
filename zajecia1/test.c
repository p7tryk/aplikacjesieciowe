#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

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

void handler_sigterm(int signal)
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
  if(signal(SIGINT, handler_sigint) == SIG_ERR)
    printf("nie zarejstrowano sigint");
  if(signal(SIGTERM, handler_sigterm) == SIG_ERR)
    printf("nie zarejstrowano sigterm");
  if(signal(SIGSTOP, handler_sigterm) == SIG_ERR)
    printf("nie zarejstrowano sigstop");
 
  printf("Hello World!\n");

  sleep(5);
  sigset_t * struktura = malloc(sizeof(sigset_t));
  sigset_t * struktura2 = malloc(sizeof(sigset_t));

  sigemptyset(struktura); //zaincjowanie struktury sigset_t
  sigaddset(struktura, SIGINT); //dodanie sygnalu sigint do struktury
  printf("blokujemy sigint\n");
  printf("sigprocmask %d\n",sigprocmask(SIG_BLOCK, struktura, NULL));



  sleep(5);
  int blokwane = sigpending(struktura2); // odczyta
  if(sigismember(struktura2, SIGINT))
     printf("SIGINT czeka na blokadzie\n");
  
  
  sleep(5);
  printf("odblokowujemy sigint\n");
  printf("sigprocmask %d\n",sigprocmask(SIG_UNBLOCK, struktura, NULL));

  
  int i;
  for(;;)
    {
      printf("*");
      fflush(stdout);
      sleep(1);
    }
  scanf("%d", &i);
  free(struktura);
  free(struktura2);
  return 0;
}
