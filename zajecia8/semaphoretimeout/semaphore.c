#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>

int main()
{
  struct timespec tm;
  sem_t semafor;
  int i=0;
  sem_init( &semafor, 0, 0);
  do
    {
      clock_gettime(CLOCK_REALTIME, &tm);
      tm.tv_sec += 3;
      i++;
      printf("i=%d\n", i);
      if (i==10)
	{
	  sem_post(&semafor);
        }
    }
  while (sem_timedwait(&semafor, &tm) == -1);
  printf("Semafor zwolniony po %d probach\n", i);
  sem_destroy(&semafor);
  return EXIT_SUCCESS;
}
