#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>

void service_up(int quiet)
{
  if(!quiet)
    {
      syslog(LOG_NOTICE,"start serwisu\n");
    }
}
void service_down(int quiet)
{
  if(!quiet)
    {
      syslog(LOG_NOTICE,"stop serwisu\n");
    }
}

void hand_sighup(int sig)
{
  service_down(0);
  syslog(LOG_NOTICE,"stop serwisu\n");
  service_up(0);
}

int main()
{
  signal(SIGHUP, hand_sighup);
  signal(SIGTERM, service_down);
  
  printf("poczatek\n");
  daemon(0,0);
  service_up(0);

  while(1)
    sleep(100);
  syslog(LOG_NOTICE,"stop serwisu\n");
}
