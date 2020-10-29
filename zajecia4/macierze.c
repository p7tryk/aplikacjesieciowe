#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

struct task{
  int col;
  int row;
};

void printMatrix(int  matrix[][3], int row, int col)
{
  printf("\nmacierz:\n");
  for(int i=0; i<row; ++i)
    for(int j=0; j<col; ++j)
      {
	printf("%d\t",matrix[i][j]);
	if(j==col-1)
	  printf("\n\n");
      }
}

void multiplyMatrix(int a[][3],int b[][3],int out[][3], int rowA, int colA,int rowB,int colB)
{
  for(int i=0;i<rowA;i++)
    {
      for(int n=0;n<rowB;n++)
	{
	  for(int k=0; k<colB;k++)
	    {
	      out[i][n]+= a[i][k] * b[k][n];
	    }
	}
    }
}

int multiplyMatrixProcess(int a[][3],int b[][3] , int rowA, int colA,int rowB,int colB, struct task process)
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



int result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int test[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int pidtable[9];

void handler_sigchild(int signal)
{
  printf("\nsigcld");
  int wstatus,pid = 0;
  pid=waitpid(-1,&wstatus,WNOHANG);
  printf("\tpid=%d\treturn=%d\n",pid,exited(wstatus));
  fflush(stdout);
  for(int i=0;i<9;i++)
    {
      if(pid==pidtable[i])
	{
	  result[i/3][i%3] = exited(wstatus);
	  break;
	}
    }
}


int main()
{
  /* if(signal(SIGCLD, handler_sigchild) == SIG_ERR) */
  /*   printf("nie zarejstrowano sigcld\n"); */


  struct task process;
  int status;
  printf("%d",wait(NULL));
  fflush(stdout);
  int pid = 1;

  int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  int b[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  int rowA=3,rowB=3,colA=3,colB=3;

  for(int i=0;i<9;i++)
    {
      if(pid>0)
	{
	  process.row=i/3;
	  process.col=i%3;
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
      for(int i=0;i<9;i++)
	{
	  if(pid==pidtable[i])
	    {
	      result[i/3][i%3] = exited(status);
	      break;
	    }
	}
    }
  printf("\nresult");
  printMatrix(result,rowA,colB);
  
  exit(0);
}
