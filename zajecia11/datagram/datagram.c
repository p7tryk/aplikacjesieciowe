#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv)
{
  socklen_t clen;
  struct sockaddr_in server;
  int sock, x, n;
  unsigned char localhost[] = {127, 0, 0, 1};
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  memcpy(&server.sin_addr, localhost, 4);
  server.sin_port = htons(10000);
  x = 0;

  //client re
  void * buff = malloc(1*sizeof(int));
  struct sockaddr_in testclient;
  //fixed port for clietn
  
  struct sockaddr_in client;
  memset(&client, 0, sizeof (client));
  client.sin_family = AF_INET;
  memcpy(&client.sin_addr, localhost, 4);
  client.sin_port = htons(20000);
  x = 0;


 

  if (bind(sock, (struct sockaddr *) &client, sizeof (client)))
    {
      perror("bind");
      // exit(1);
    }
  
  
  for (;;)
    {
      n = sendto(sock, &x, sizeof (int), 0, (struct sockaddr *) &server, sizeof (server));
      printf("Wysłano bajtów: %d, wartość %d\n", n, x);
      x++;
      sleep(1);
      //czekam na potwierdzenie
      //recv(sock, buff,sizeof(buff), 0);
      recvfrom(sock, buff, sizeof (buff), 0, (struct sockaddr *) &testclient, &clen);
      unsigned char *a = (unsigned char *) &testclient.sin_addr;
      printf("Od %d.%d.%d.%d:%d otrzymano wartosc %d\n", a[0], a[1], a[2], a[3], ntohs(testclient.sin_port), x);
      
      printf("potwierdzono %d\n",*(int*)buff);
      
    }

  
  return (EXIT_SUCCESS);
}
