#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


void * kodWatku(void *arg) 
{
    sleep(*((int *)arg));
    return (arg);
}


int main(int argc, char *argv[]) 
{
    pthread_t t1, t2, t3;
    int start;
    void *status;
    int znaki[] = {3,5,8};
    pthread_create(&t1, NULL, kodWatku, znaki);
    
    pthread_create(&t2, NULL, kodWatku, znaki+1);
    pthread_create(&t3, NULL, kodWatku, znaki+2);
    start = time(NULL);
    pthread_join(t1,&status);
    printf("odczytano status = %d, po czasie: %ld\n", *((int*)status), time(NULL)-start);
    
    pthread_join(t2,&status);
    printf("odczytano status = %d, po czasie: %ld\n", *((int*)status), time(NULL)-start);
    
    pthread_join(t3,&status);
    printf("odczytano status = %d, po czasie: %ld\n", *((int*)status), time(NULL)-start);
    return 0;
}
