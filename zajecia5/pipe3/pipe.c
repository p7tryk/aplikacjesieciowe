//TODO  potwierdzenie zapisu

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
  int n, i;
  int forwardpipe[2];
  pipe(forwardpipe);
  int returnpipe[2];
  pipe(returnpipe);
  if(fork() == 0)
    {
      
      close(forwardpipe[1]);
      close(returnpipe[0]);
      /* proces potomny czyta */
      for (;;)
	{
	  read(forwardpipe[0], &n, sizeof (int));
	  write(returnpipe[1],&n,sizeof(int));
	  for (i = 0; i < n; i++)
	    {
	      printf("dziecko: %d\n", n);
	      fflush(stdout);
	      sleep(1);
	    }
	  if(i>0)
	    return 0;
	}
      

    }
  else
    {
      close(forwardpipe[0]);
      close(returnpipe[1]);
      /* proces macierzysty pisze */
      for (;;)
	{
	  int input;
	  printf("parent: ");
	  fflush(stdout);
	  scanf("%d", &n);
	  write(forwardpipe[1], &n, sizeof (int));
	  
	  while(read(returnpipe[0],&input,sizeof(int))!=0)
	    {
	      if(input==n)
		{
		  printf("parent: potwierdzono %d\n", n);
		  fflush(stdout);
		  //ladnie wychodzi
		  wait(NULL);
		  return 0;
		}
	      sleep(1);
	    }
	}
    }
  return (EXIT_SUCCESS);
}
