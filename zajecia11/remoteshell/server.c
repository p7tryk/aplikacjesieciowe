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
struct thread_info
{
  int socketfd;
  int threadnum;
};

void handler_sigcld(int sig)
{
  int status;
  while (waitpid(-1, &status, WNOHANG) > 0);
}

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
      /* sprintf(buffer,"hi from server\n"); */
      /* int sentbytes = send(localinfo->socketfd,buffer, strlen(buffer),0); */
      /* if(sentbytes>0) */
      /* 	{ */
      /* 	  printf("\nThread %d:\tsending to socket:\n",localinfo->threadnum); */
      /* 	  write(1, buffer, sentbytes); */
      /* 	} */
      /* else */
      /* 	{ */
      /* 	  perror("recv"); */
      /* 	  break; */
      /* 	} */
    }



  printf("Thread %d:\tFinishing\n",localinfo->threadnum);
  free(buffer);
  close(localinfo->socketfd);
  free(localinfo);
  return NULL;
}

int main()
{
  struct sockaddr_in server;

  int sock, opt;
  signal(SIGCLD, handler_sigcld);
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

  int threadcount = 0;

  while(1)
    {
      int clientsocket;
      clientsocket=accept(sock,NULL, NULL);
      if(clientsocket>0)
	{
	  struct thread_info * newthread = malloc(sizeof(struct thread_info));
	  pthread_t thread;
	  newthread->threadnum = threadcount;
	  printf("spinning thread %d to accept\n", threadcount++);
	 
	  newthread->socketfd = clientsocket;
	  pthread_create(&thread,NULL,socketthread,newthread);
	  /* socketthread(newthread); */
	}
      else
	perror("accept");
    }
}
