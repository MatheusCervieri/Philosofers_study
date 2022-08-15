#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//gcc main.c -lpthread | ./a.out 

/*
    EXPLICAÇÃO MUTEX. 
    Quando usamos thereads podemos alterar o valor de uma variavel dentro de varias thereads simultaneamente. 
    Isso causa um problema, porque ao mexermos na variavel com algum processo de iteração por exemplo, podemos não obter o resultado esperado.
    Isso acontece porque no assembly um while é mais ou menos isso:
    //read number
    //increment number
    //write number 
    Se não usar o mutex podemos ler um valor que não foi incrimentado em um processo, mas em outro processo esse valor já foi incrementado. Então, nesse caso,
    iremos acabar escrevendo no processo antigo e isso gera um problema.
    Esse erro sem o mutex é chamado de Data racing. 
*/

int number = 0; 

pthread_mutex_t mutex1; 

void * workerThereadFunc (void * tid)
{
   int i = 0;
   while (i < 10000000)
    {
        pthread_mutex_lock(&mutex1);
        number++;
         pthread_mutex_unlock(&mutex1);
        i++;
    }
}

/*
    The main difference beetweem threads and process are that when you change a variable in a thread it changes in both threads because the threads shere
    a process. 
*/

/*
     The race condintion problen: It is basically the process of increment in a variable doing in the same time by multiples process. It causes a problen.
*/

int main ()
{
    pthread_t tid0;
    pthread_t tid1;

    pthread_mutex_init(&mutex1, NULL);
   //struct que guarda as informações da theread;
    //the second parameter is a struct that describes the behavior 
    //of the theread. NULL --> deafult behavior.
    //pointer to a fucntion that the theread will execute. 
    //the forth parameter is the parameter that will be passed to the workerTheradFunc
    pthread_create(&tid0, NULL, workerThereadFunc, (void *)&tid0);
    pthread_create(&tid1, NULL, workerThereadFunc, (void *)&tid1);


    pthread_join(tid0, NULL); //Thread wait function. 
    pthread_join(tid1, NULL); //Thread wait function. 
    printf("The number is %d", number);
    pthread_mutex_destroy(&mutex1);

    //Forces main to wait our theread. The problen
    //is that we cant use this in philosofers. If we dont add this the main function
    //will exit before the function can do this work. 
    return (0);
}