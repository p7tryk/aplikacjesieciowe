#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

struct wiadomosc wysylka;


//CLIENT
void sendcommand(char * command, int sock, int flags, char * buffer);

int main(int argc, char** argv)
{

  sprintf(wysylka.lokalizacja,"/home/");
   
 

  //niewazne
  int clientno = 0;
  if(argc>1)
    clientno = atoi(argv[1]);
  //przygotowanie polaczenia
  struct sockaddr_in server;
  unsigned char localhost[] = IP_ADDR;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  memcpy(&server.sin_addr, localhost, 4);
  server.sin_port = htons(PORTNO);
  if (connect(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("connect");
      exit(0);
    }



  char * newmessage  = wysylka.command;
  char * buffer = malloc(sizeof(char)*BUFSIZE);

  //make it nonblock
  fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK); 

  while(1)
    {
      //while true bo fgets jest blokujace
      
      //cos dziwnego sie dzialo wiec lepiej wyclearowac bufor mozna w sumie calloc()
      for(int i = 0; i<BUFSIZE;i++)
	buffer[i] = '\0'; 

      //command prompt
      printf(ANSI_COLOR_GREEN "" ANSI_BOLD "\nuselesshell" ANSI_COLOR_BLUE "%s $ " ANSI_COLOR_RESET, wysylka.lokalizacja);
       


      fgets(newmessage,BUFSIZE,stdin);

      if( strstr(newmessage, "cd")!=0){
      
      if(sscanf(newmessage, "%s %s",wysylka.lokalizacja ,wysylka.lokalizacja )==0){
      perror("sscanf");
      };
      //printf("%d ",sscanf(newmessage, "%s %s",wysylka.lokalizacja ,wysylka.lokalizacja));
      sendcommand("pwd",sock, 0 , buffer);
      continue;
      }


      if(strcmp(newmessage,"exit")==0)
	break;
      
      //newmessage[strlen(newmessage)] = EOF;
      sendcommand(newmessage,sock, 0 , buffer);
    }
  close(sock);
  free(newmessage);
  free(buffer);
  return (EXIT_SUCCESS);
}

void sendcommand(char * command, int sock, int flags, char * buffer)
{
  
  printf("\nsending:\n%s", command);
  int sentbytes = send(sock, (void*) &wysylka, sizeof(wysylka), 0);
  if(sentbytes > 0)
    printf("\nwritten %d*\n",sentbytes-1);
  else
    {
      perror("send");
      printf("broken socket\n");
      exit(-1);
    }
  sleep(1);
  int receivedbytes = 0;
  //ten socket jest ustawiony na O_NONBLOCK wiec uzywamy for loopa zeby zebrac dane
  for(receivedbytes = recv(sock,buffer,BUFSIZE,flags);receivedbytes>0;receivedbytes = recv(sock, buffer, BUFSIZE,flags))
    {
      printf("\nreceived %d\n",receivedbytes);
      write(1, buffer, receivedbytes);
    }
  if(receivedbytes<0)
    {
      perror("recv");
    }
}
