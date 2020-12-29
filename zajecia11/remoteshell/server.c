#include "define.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
//SERVER

struct thread_status
{
  int status[MAXTHREADS];
  pthread_t thread_array[MAXTHREADS];
} global_threads;

struct thread_info
{
  int socketfd;
  int threadnum;
};

void shell(char * command, int fd)
{
  int pid = fork();
  if(pid==0)
    {
      dup2(fd, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      execl("/bin/bash", "bash", "-c", command, (char *) NULL);
    }
  else
    waitpid(pid,NULL,0);
}
void * socketthread(void * arg)
{
  struct thread_info * localinfo = (struct thread_info *) arg;
  char * buffer = malloc(sizeof(char)*BUFSIZE);

  while(1)
    {
      int receivedbytes = recv(localinfo->socketfd,buffer, BUFSIZE, 0);
      if(receivedbytes>0)
	{
	  printf("\nThread %d:\treceiving from socket:\n",localinfo->threadnum);
	  write(1, buffer, receivedbytes);
	  printf("\n");
	}
      else
	{
	  perror("recv");
	  break;
	}
      buffer[receivedbytes+1]=EOF;
      shell(buffer,localinfo->socketfd);
    }



  printf(ANSI_COLOR_BLUE "Thread %d:\tFinishing\n" ANSI_COLOR_RESET,localinfo->threadnum);
  free(buffer);
  close(localinfo->socketfd);
  global_threads.status[localinfo->threadnum] = 0;
  free(localinfo);
  pthread_exit(NULL);
}
int queuejob()
{
  while(1)
    {
    for(int i=0;i<MAXTHREADS;i++)
      {
	//printf("thread %d = %d\n",i,global_threads.status[i]);
	if(global_threads.status[i]==0)
	  {
	    global_threads.status[i]=1;
	    return i;
	  }
      }
    printf(ANSI_COLOR_RED "no empty threads!\nwaiting\n" ANSI_COLOR_RESET);
    sleep(5);
    }
}

void initthreads()
{
  for(int i=0;i<MAXTHREADS;i++)
    global_threads.status[i] = 0;
}

int main()
{
  struct sockaddr_in server;

  int sock, opt;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORTNO);
  if (bind(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("bind");
      exit(1);
    }

  listen(sock, 5);

  initthreads();

  while(1)
    {
      struct sockaddr_in test;
      socklen_t testlen;
      int clientsocket;
      clientsocket=accept(sock,(struct sockaddr*) &test, &testlen);
      if(clientsocket>0)
	{
	  struct thread_info * newthread = malloc(sizeof(struct thread_info));
	  newthread->threadnum = queuejob();
	  unsigned char *a = (unsigned char *) &test.sin_addr;
	  printf(ANSI_COLOR_GREEN "spinning thread %d to accept %d.%d.%d.%d:%d\n" ANSI_COLOR_RESET, newthread->threadnum,a[0],a[1],a[2],a[3], ntohs(test.sin_port));
	 
	  newthread->socketfd = clientsocket;
	  pthread_create(&global_threads.thread_array[newthread->threadnum],NULL,socketthread,newthread);
	  /* socketthread(newthread); */
	}
      else
	perror("accept");
    }
}
