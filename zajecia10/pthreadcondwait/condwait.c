/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   main.c
 * Author: pawel
 *
 * Created on 22 listopada 2020, 20:06
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex;// = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;// = PTHREAD_COND_INITIALIZER;
int licznik = 0;

void * kodWatku1(void *arg) 
{
  int n;
  pthread_mutex_lock(&mutex);
  while(licznik==0)
    {
      pthread_cond_wait(&cond, &mutex);
    }
  for(n=0;n<10;n++)
    {
      printf("%c", *((char *) arg));
      fflush(stdout);
      sleep(1); 
    }
  licznik=0;
  pthread_cond_signal(&cond);
  printf("\n");
  pthread_mutex_unlock(&mutex);
  return (NULL);
}

void * kodWatku(void *arg) 
{
  int n;
  pthread_mutex_lock(&mutex);
  while(licznik==1)
    {
      pthread_cond_wait(&cond, &mutex);
    }
  for(n=0;n<10;n++)
    {
      printf("%c", *((char *) arg));
      fflush(stdout);
      sleep(1); 
    }
  licznik = 1;
  pthread_cond_signal(&cond);
  printf("\n");
  pthread_mutex_unlock(&mutex);
  return (NULL);
}
int main(int argc, char *argv[]) 
{
  pthread_t t1, t2;
  char s[] = "AB";
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);
  srand(time(NULL));
  pthread_create(&t1, NULL, kodWatku1, s);
  pthread_create(&t2, NULL, kodWatku, s + 1);
  pthread_join(t1,NULL);  
  pthread_join(t2,NULL);  
    
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  pthread_attr_destroy(&attr);
    
  return EXIT_SUCCESS;
}
