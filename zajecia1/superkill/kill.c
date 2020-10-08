#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

// wysyla dany sygnal kilka razy

int main(int argc, char *argv[])
{
  if(argc != 4)
    {
      printf("uzywanie:\n%s sygnal ilosc pid\n", argv[0]);
      return 0;
    }
  pid_t pid = 0;
  int ilosc = 0;
  int sygnal = 0;

  sscanf(argv[1],"%d", &sygnal);
  sscanf(argv[2],"%d",  &ilosc);
  sscanf(argv[3],"%d",  &pid);

  printf("sygnal: %d\nilosc: %d\npid: %d\n", sygnal, ilosc, pid);

  for(ilosc;ilosc>0;ilosc--)
    {
      if(kill(pid, sygnal)==0)
	printf("wysyłam signal %d\n",sygnal);
      else
	printf("Nie udalo sie wyslać %d\n", sygnal);
      sleep(1);
    }

  
}
