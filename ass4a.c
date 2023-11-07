#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

//semaphore variables
sem_t empty, full;
//mutex variable
pthread_mutex_t mutex;
int buffer[5];
int count = 0;

void *producer(void *arg){
    long int num = (long int)arg;

    //producer is trying to produce data
    sem_wait(&empty);

    //producer is allowed to produce data
    pthread_mutex_lock(&mutex);

    //producer is producing data
    buffer[count] = rand()%10;
    printf("\nProducer %ld Produced : %d\n", num+1, buffer[count]);
    count++;
    sleep(1);

    //producer will now release the mutex lock after producing data
    pthread_mutex_unlock(&mutex);

    //producer will increment full slots
    sem_post(&full);

    pthread_exit(NULL);
}

void *consumer(void *arg){
    long int num = (long int)arg;

    //consumer will try to consume
    sem_wait(&full);

    //consumer is allowed to consume data
    pthread_mutex_lock(&mutex);

    //consumer is consuming the data
    count--;
    printf("\nConsumer %ld Consumed : %d\n", num+1, buffer[count]);
    sleep(1);

    //consumer will release lock on mutex after consuming
    pthread_mutex_unlock(&mutex);

    //consumer will increment empty slots
    sem_post(&empty);

    pthread_exit(NULL);
}

int main(){
    int np, nc;
    printf("\nEnter number of producers : ");
    scanf("%d", &np);
    printf("\nEnter number of consumers : ");
    scanf("%d", &nc);

    //initializing semaphore variable
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    //iniotializing mutex variable
    pthread_mutex_init(&mutex, NULL);

    unsigned long int i;
    //thread variables
    pthread_t p[10], c[10];
    //creating producer threads
    for(i=0; i<np; i++){
        pthread_create(&p[i], NULL, producer, (void *)i);
    }
    //creating consumer threads
    for(i=0; i<nc; i++){
        pthread_create(&c[i], NULL, consumer, (void *)i);
    }

    //join producer threads
    for(i=0; i<np; i++){
        pthread_join(p[i], NULL);
    }
    for(i=0; i<nc; i++){
        pthread_join(c[i], NULL);
    }

    return 0;
}


