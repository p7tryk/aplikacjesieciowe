//TODO  potwierdzenie zapisu

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
  int n, i;
  int p[2];
  pipe(p);
  int p2[2];
  pipe(p2);
  if(fork() == 0)
    {
      
      close(p[1]);
      close(p2[0]);
      /* proces potomny czyta */
      for (;;)
	{
	  read(p[0], &n, sizeof (int));
	  write(p2[1],&n,sizeof(int));
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
      close(p[0]);
      close(p2[1]);
      /* proces macierzysty pisze */
      for (;;)
	{
	  int input;
	  printf("parent: ");
	  fflush(stdout);
	  scanf("%d", &n);
	  write(p[1], &n, sizeof (int));
	  
	  while(read(p2[0],&input,sizeof(int))!=0)
	    {
	      fflush(stdout);
	      if(input==n)
		{
		  printf("parent: potwierdzono %d\n", n);
		  fflush(stdout);
		  wait(NULL);
		  return 0;
		}
	      sleep(1);
	    }
	}
    }
  return (EXIT_SUCCESS);
}
