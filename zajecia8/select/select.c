#include <sys/mman.h> 
#include <fcntl.h> 
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#define SIZE    80   //  Dlugosc linii

typedef struct {
  char buf[SIZE];
  sem_t mutex;    
} bufor_t;

int main(int argc, char *argv[])
{
  int i, stat, pid, size, fd;
  bufor_t *buf;
  // Utworzenie segmentu --------------------------- 
  shm_unlink("bufor");
  fd = shm_open("bufor", O_RDWR | O_CREAT, 0774);
  if (fd == -1)
    {
      perror("open");
      exit(-1);
    }
  printf("fd: %d\n", fd);
  size = ftruncate(fd, sizeof (bufor_t));
  if (size < 0)
    {
      perror("trunc");
      exit(-1);
    } 
  // Odwzorowanie segmentu fd w obszar pamieci procesow
  buf = (bufor_t *) mmap(0, sizeof (bufor_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (buf == NULL)
    {
      perror("map");
      exit(-1);
    } 
  if (sem_init(&(buf->mutex), 1, 1))
    {
      perror("mutex");
      exit(0);
    }
  if(fork() == 0) 
    {       
      for(i=0;i<10;i++) 
        {
	  sem_wait(&(buf->mutex));        
	  printf("Potomny\n");            
	  sprintf(buf->buf, "Komunikat %d", i);
            
            
	  sem_post(&(buf->mutex));
	  sleep(1);
        }
      shm_unlink("bufor");
      exit(i);
    } 
  for (i = 0; i < 10; i++)
    {
      sem_wait(&(buf->mutex));
      if(strlen(buf->buf)>0)
	 printf("Macierzysty - odebrano %s\n", buf->buf);
      
      fflush(stdout);
        
      sem_post(&(buf->mutex));
      sleep(1);        
    }      
  pid = wait(&stat);
  shm_unlink("bufor");
  sem_destroy(&(buf->mutex));  
  return EXIT_SUCCESS;
}
