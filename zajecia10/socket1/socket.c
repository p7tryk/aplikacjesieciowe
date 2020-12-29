#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
  //unsigned char target_addr[] = { 192,168,0,196};
  unsigned char target_addr[] = {127,0,0,1};
  
  /* struct hostent *ghbn = gethostbyname("servbuntu.lan"); */
  /* char * target_addr; */
  /* target_addr = inet_ntoa(*(struct in_addr *)ghbn->h_name); */
  
  struct sockaddr_in server;
  
  int sock;
  

  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock<0)
    return 0;
  
  memset(&server,0,sizeof(server));
  server.sin_family=AF_INET;
  memcpy(&server.sin_addr, target_addr, 4);
  server.sin_port = htons(80);

  if(connect(sock, (struct sockaddr*) &server, sizeof(server)))
    {
      perror("connect");
      exit(1);
    }
  
  char request[] = "GET / HTTP/1.1\r\nHost: 127.0.0.1:80\r\n\r\n";
  char * buffer = (char *) malloc(500*sizeof(char));
  
  /* write(sock, request, sizeof(buffer)); */
  
  /* read(sock,buffer, 500*sizeof(char)); */

  int n = 0;
  printf("sending:\n%s",request);

  if (write(sock, request, sizeof(request))>= 0) 
    {

      while ((n = read(sock, buffer, 500)) > 0)
	{
	  printf("\nreading %d\n",n);
	  write(STDOUT_FILENO, buffer, n);
	}   
    }
  
  close(sock);
  return  0;

}
