#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv)
{
  //SERVER
  struct sockaddr_in server, client;
  socklen_t clen;
  int sock, x;
  unsigned char *a;
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  if (bind(sock, (struct sockaddr *) &server, sizeof (server)))
    {
      perror("bind");
      exit(1);
    }
  for (;;)
    {
      clen = sizeof (client);
      recvfrom(sock, &x, sizeof (int), 0, (struct sockaddr *) &client, &clen);
      a = (unsigned char *) &client.sin_addr;
      printf("Od %d.%d.%d.%d:%d otrzymano wartosc %d\n", a[0], a[1], a[2], a[3], ntohs(client.sin_port), x);
      //confirm
      int n = sendto(sock, &x, sizeof (int), 0, (struct sockaddr *) &client, sizeof (client));
      printf("odeslano %d\n",x);
    }
  return (EXIT_SUCCESS);
}
