#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void child()
{
  printf("jestem dzieckiem\n");
}
void parent()
{
  printf("jestem rodzicem\n");
}

void wypisz(char znak)
{
  for(;;)
    {
      printf("%c", znak);
      fflush(stdout);
      sleep(1);
    }
}

//TODO sprawdzic jakie zmiany sa w jednym procesie
int main()
{


  FILE * fileptr;
  int pid;
  char * buffer = malloc(sizeof(char)*512);
  int fd;

  
  fd = open("fork.c",O_RDONLY);

  char c;
  pid = fork();

  while(read(fd,&c,1) ==1)
    {
      if (pid>0)
	{
	  printf("%c",c);
	  fflush(stdout);
	}
    }
  
  /* fgets(buffer,10,fileptr); */
  /* printf("Plik:\n%s\n", buffer); */
  /* printf("%p",fileptr); */
  /* sleep(1); */

  printf("\n\n");
  int liczba = 0;
  char * ptr = malloc(sizeof(char)*512);

  void (*funptr)(void) = &parent;

  ptr = "initial";

  
  
  
  if(!pid)
    {
      liczba++;
      ptr = "dziecko";
      printf("dziecko\n");
      funptr = &child;
    }
  else
    {
      printf("rodzic\n");
      /* fgets(buffer,512,fileptr); */
    }

  printf("pid %d\n",(int)pid);
  printf("int \t%d\t %p\n",liczba,&liczba);
  printf("string \t%s\t%p\n",ptr,ptr);
  printf("funkcja %p\n",funptr);
  fflush(stdout);
  funptr();
  printf("fclose() = %d\n",close(fd));

  sleep(5);

  return 0;
}
