#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFSIZE 256


int main(int argc, char** argv, char ** envp)
{
  printf("Witaj w ke$Ha");
  
  char * cwd = malloc(sizeof(char)*BUFFSIZE);
  char ** a = malloc(sizeof(char)*64);
  char * buffer = malloc(sizeof(char)*BUFFSIZE);
  char * string = malloc(sizeof(char)*BUFFSIZE);
  
  
  int n,status;

  FILE * fd;

  for(;;)
    {
      if(getcwd(cwd,sizeof(cwd)))
	 printf("\nke$Ha:%s",cwd);
      else
	{
	  //printf("error cwd\n");
	  printf("\nke$ha:$ ");
	}
      if(fgets(buffer,256,stdin) == NULL)
	break;
      
      fd = popen(buffer,"r");

      while(fgets(string,sizeof(string),fd)!=NULL)
	printf("%s",string);
      fflush(stdout);
      pclose(fd);
    }



  return 0;
}
