#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFSIZE 256

int exited(int status)
{
  if(WIFEXITED(status))
    {
      return WEXITSTATUS(status);
    }
  else if(WIFSIGNALED(status))
    {
      return WTERMSIG(status);
    }
  return 0;
}

int main(int argc, char** argv, char ** envp)
{
  printf("Witaj w ke$Ha");
  
  char * cwd = malloc(sizeof(char)*BUFFSIZE);
  char ** a = malloc(sizeof(char)*64);
  char * buffer = malloc(sizeof(char)*BUFFSIZE);

  int n,status;

  for(;;)
    {
      if(getcwd(cwd,sizeof(cwd)))
	 printf("\nke$Ha:%s",cwd);
      else
	{
	  //printf("error cwd\n");
	  printf("\nke$ha:");
	}
      if(fgets(buffer,256,stdin) == NULL)
	break;
        
      /* if((a[0]=strtok(buffer," \t\n\r"))==NULL) */
      /* 	continue; */

      /* for(n=1;a[n];n++) */
      /* 	strtok(NULL, " \t\n\r"); */

      /* if(fork()==0) */
      /* 	{ */
      /* 	  printf("%s\n",a[0]); */
      /* 	  execvp(a[0],a); */
      /* 	  perror("execvp"); */
      /* 	  exit(0); */
      /* 	} */
      /* else */
      /* 	{ */
      /* 	  wait(&status); */
      /* 	  printf("exit status = %d", exited(status)); */
      /* 	} */

      status = system(buffer);
      printf("exit = %d",status);
      
    }



  return 0;
}
