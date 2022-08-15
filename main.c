#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//gcc main.c -lpthread | ./a.out 

void * workerThereadFunc (void * tid)
{
    long * myId = (long *) tid;
    printf("HELLO WORLD! This is a thread %ld \n", *myId);
}

int main ()
{
    pthread_t tid0;
    pthread_t tid1;
    pthread_t tid2; //struct que guarda as informações da theread;
    //the second parameter is a struct that describes the behavior 
    //of the theread. NULL --> deafult behavior.
    //pointer to a fucntion that the theread will execute. 
    //the forth parameter is the parameter that will be passed to the workerTheradFunc
    pthread_create(&tid0, NULL, workerThereadFunc, (void *)&tid0);
    pthread_create(&tid1, NULL, workerThereadFunc, (void *)&tid1);
    pthread_create(&tid2, NULL, workerThereadFunc, (void *)&tid2);

    pthread_exit(NULL); //Forces main to wait our theread. The problen
    //is that we cant use this in philosofers. If we dont add this the main function
    //will exit before the function can do this work. 
    return (0);
}