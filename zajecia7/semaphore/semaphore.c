#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
  sem_t *mutex = NULL;
  char name[] = "test.out";
  int status;
 
  int fd;
  fd = shm_open(name, O_RDWR | O_CREAT, 0664);
  mutex = (sem_t*) mmap(0, sizeof(mutex), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(mutex == NULL)
    exit(-1);

  if(fork() == 0)
    {
      sleep(3);
      mutex = sem_open("mutex", 1);

      
      for(int i=0; i<10;i++)
	{
	  sem_wait(mutex);
	  printf("%d %c\n", i, 'C');
	  fflush(stdout);
	  sem_post(mutex);
	  sleep(1);
	}
     
      sleep(1);
      exit(0);
    }
  else
    {      
      mutex =  sem_open("mutex", O_CREAT, S_IRWXU, 1);
      sleep(3);
      for(int i=0; i<10;i++)
	{
	  sem_wait(mutex);
	  printf("%d %c\n", i, 'B');
	  fflush(stdout);
	  sem_post(mutex);
	  sleep(1);
	}
      sleep(1);
    }
  while(wait(&status)>0);

  sem_close(mutex);
  sem_unlink("mutex");
  return 0;
}


