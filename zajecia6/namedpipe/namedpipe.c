#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define FIF01 "./fifo.1"
#define FILE_MODE 0666
#define MAX_LINE 1024

int main(int argc, char *argv[])
{
  int writefd = 0, readfd, res, len;
  char buff[1024], c;
  if ((mkfifo(FIF01, FILE_MODE) < 0))
    {
      printf("can't create %s", FIF01);
      fflush(stdout);
    }
  if (fork() == 0)
    {
      int i;
      writefd = open(FIF01, O_WRONLY, 0);
      printf("sciezka: %s", FIF01);
      fflush(stdout);
      for (i = 0; i < 10; i++)
	{
	  /*fgets(buff, MAX_LINE, stdin);*/
	  sprintf(buff, "%d", i);
	  len = strlen(buff);
	  /* fgets() gwarantuje bajt pusty na końcu */
	  if (buff[len - 1] == '\n')
	    {
	      len--;
	    }
	  write(writefd, buff, len);
	  sleep(1);
	}
    }
  else
    {
      readfd = open(FIF01, O_RDONLY, 0);
      do
	{
	  res = read(readfd, &c, 1); // Odczyt z pliku FIFO
	  printf("Odczytano: %c \n", c);
	}
      while (res > 0);
    }
  wait(NULL);
  close(writefd);
  unlink(FIF01);
  return EXIT_SUCCESS;
}
