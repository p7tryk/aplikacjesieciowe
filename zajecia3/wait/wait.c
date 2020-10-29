#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>




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

void handler_sigchild(int signal)
{
  printf("\nsigcld");
  int wstatus,pid = 0;
  while(pid>0)
    {
      pid=waitpid(-1,&wstatus,WNOHANG);
      if(pid>0)
	printf("\tpid=%d\treturn=%d\n",pid,exited(wstatus));
      fflush(stdout);
    }
}

int main()
{
  if(signal(SIGCLD, handler_sigchild) == SIG_ERR)
    printf("nie zarejstrowano sigcld\n");
  
  int status;
  printf("%d",wait(NULL));
  fflush(stdout);
  int pid;

  pid = fork();

  for(int i=0;i<10;i++)
    {
      if(!pid)
	{
	  for(int i=0;i<8;i++)
	    {
	      printf("#\n");
	      fflush(stdout);
	      sleep(1);
	    }
	  exit(10);
	}
      else
	pid = fork();
    }
  
   for(int i=0;i<10;i++)
    {
      if(!pid)
	{
	  for(int i=0;i<10;i++)
	    {
	      printf("*\n");
	      fflush(stdout);
	      sleep(1);
	    }
	  exit(20);
	}
      else
	pid = fork();
    }
   //sleep(20);
  pid=0;
  /* while(pid>=0) */
  /*   { */
      pid=wait(&status);
      printf("\npid=%d\treturn=%d\n",pid,exited(status));
  /*     fflush(stdout); */
  /*   } */
  
  exit(0);
}
