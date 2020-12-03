#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREADS 12
#define START 1
#define END 10000000

//TO JEST SUPER BARDZIEJ SKOMPLIKOWANE NIZ POWINNO BYC

struct meta{
  int poczatek;
  int koniec;
  int threads;
  int  * values;
  int offset;
  pthread_mutex_t lock;
};



int singlethread(int poczatek, int koniec);
int czyPierwsza(int n);
int multithread(int poczatek, int koniec);
void * thread(void * arg);

int main(int argc, char *argv[])
{
    int poczatek=START, koniec=END;

    time_t timestart;
    time_t timeend;
    
    timestart = time(NULL);
    int single = singlethread(poczatek, koniec);
    timeend = time(NULL);
    
    printf("W [%d-%d] znajduje się: %d liczb pierwszych\nzajelo to %d wątkom %d sekund\n", poczatek, koniec, single, 1,(int)(timeend-timestart));
    
    timestart = time(NULL);
    int multi = multithread(poczatek, koniec);
    timeend = time(NULL);
    
    printf("W [%d-%d] znajduje się: %d liczb pierwszych\nzajelo to %d wątkom %d sekund\n", poczatek, koniec, multi, THREADS,(int)(timeend-timestart));
    exit(EXIT_SUCCESS);
}

int singlethread(int poczatek,int koniec)
{
  int i,ileLiczbPierwszych =0;
  for(i=poczatek;i<=koniec;i++)
    {    
      if(czyPierwsza(i))  
	ileLiczbPierwszych++;  
    }
  return ileLiczbPierwszych;
}


int multithread(int poczatek, int koniec)
{
  int threads = THREADS;
  /* if(threads<(koniec-poczatek)) //dla bardzo malych zakresow */
  /*   threads=koniec-poczatek; */

  

  pthread_t * tid = malloc(threads*sizeof(pthread_t));
  
  struct meta * args = (struct meta*)malloc(sizeof(struct meta));

  args->poczatek=poczatek;
  args->koniec=koniec;
  args->threads=threads;
  args->offset=0;
  //return array
  args->values = (int*) malloc(threads*sizeof(int));
  pthread_mutex_init(&(args->lock),NULL);

  //create threads
  
  for(int i=0; i<threads;i++)
    {
      pthread_create(&tid[i],NULL,thread,args);
    }


  //asdasda

  //wait all threads;
  for(int i=0; i<threads;i++)
    {
      //printf("creating thread=%d\n",i);
      fflush(stdout);
      pthread_join(tid[i], NULL);
    }
  //count all threads;
  int liczbapierwszych =0;
  for(int  i=0; i<threads;i++)
    {
      liczbapierwszych += args->values[i];
    }

  //free memory
  free(args->values);
  free(args);
  return liczbapierwszych;
}

void * thread(void * arg)
{
  //lock and copy local data
  struct meta * input = arg;
  pthread_mutex_lock(&input->lock);
  
  int poczatek=input->poczatek;
  int koniec=input->koniec;
  int thread=input->threads;
  int offset=input->offset;
  input->offset++;

  pthread_mutex_unlock(&input->lock);

  //printf("im offset %d\n",offset);
  fflush(stdout);
  
  int liczbapierwszych=0;
  for(poczatek=poczatek+offset; poczatek<koniec;poczatek+=thread)
    {
      //printf("czyPierwsza(%d)\n",poczatek);
      if(czyPierwsza(poczatek))
	liczbapierwszych++;
    }

  input->values[offset] =liczbapierwszych;
  return NULL;
}


int czyPierwsza(int n)
{
    int i;
    for (i = 2; i * i <= n; i++)
    {
        if ((n % i) == 0)
        {
            return 0;
        }
    }
    return 1;
}
