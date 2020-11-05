#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "matrixoperations.c"
#define SIZE 3

struct task{
  int col;
  int row;
};



int multiplyMatrixProcess(int a[][SIZE],int b[][SIZE] , int rowA, int colA,int rowB,int colB, struct task process)
{
  int result = 0;
  
  for(int i = 0; i<colB;i++)
    result+=a[i][process.col]*b[process.row][i];


  return result;
}

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



int result[SIZE][SIZE] = {{0,0,0},{0,0,0},{0,0,0}};
int test[SIZE][SIZE] = {{0,0,0},{0,0,0},{0,0,0}};
int pidtable[SIZE*SIZE];

void handler_sigchild(int signal)
{
  printf("\nsigcld");
  int wstatus,pid = 0;
  pid=waitpid(-1,&wstatus,WNOHANG);
  printf("\tpid=%d\treturn=%d\n",pid,exited(wstatus));
  fflush(stdout);
  for(int i=0;i<SIZE*SIZE;i++)
    {
      if(pid==pidtable[i])
	{
	  result[i/SIZE][i%SIZE] = exited(wstatus);
	  break;
	}
    }
}


int main()
{
  if(signal(SIGCLD, handler_sigchild) == SIG_ERR)
    printf("nie zarejstrowano sigcld\n");


  struct task process;
  int status;
  printf("%d",wait(NULL));
  fflush(stdout);
  int pid = 1;

  int a[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};
  int b[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};
  int rowA=SIZE,rowB=SIZE,colA=SIZE,colB=SIZE;

  for(int i=0;i<SIZE*SIZE;i++)
    {
      if(pid>0)
	{
	  process.row=i/SIZE;
	  process.col=i%SIZE;
	  pid = fork();
	  pidtable[i] = pid;
	}
      if(pid==0)
	{
	  return multiplyMatrixProcess(a,b,rowA,colA,rowB,colB,process);
	}
    }

  multiplyMatrix(a,b,test,rowA,colA,rowB,colB);
  printf("test mnozenie\n");
  printMatrix(test,rowA,colB);

  pid=0;
  while(pid>=0)
    {
      pid=wait(&status);
      printf("\npid=%d\treturn=%d",pid,exited(status));
      fflush(stdout);
      for(int i=0;i<SIZE*SIZE;i++)
	{
	  if(pid==pidtable[i])
	    {
	      result[i/SIZE][i%SIZE] = exited(status);
	      break;
	    }
	}
    }
  printf("\nresult");
  printMatrix(result,rowA,colB);
  
  exit(0);
}
