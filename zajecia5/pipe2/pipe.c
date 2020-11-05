#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFSIZE 256


int main(int argc, char** argv, char ** envp)
{
  if(argc<3)
    {
      printf("za malo argumentow");
      return 0;
    }

  char * buffer = malloc(sizeof(char)*BUFFSIZE);
  
  FILE * input;
  FILE * output;

  input = popen(argv[1],"r");
  
  output = popen(argv[2],"w");

  while(fgets(buffer,sizeof(buffer),input)!=NULL)
    fputs(buffer, output);

  pclose(input);
  pclose(output);

  return 0;
}
