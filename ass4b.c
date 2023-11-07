#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t wr, mutex;
int readcount = 0;
int a=10;

void *reader(void *arg){
    long int num = (long int) arg;

    //all readers increasing readcount one by one
    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);

    //if its a first reader 
    if(readcount == 1){
        pthread_mutex_lock(&wr);
    }

    printf("\n\nReader %ld is now in critical section.", num);
    printf("\nReader %ld reading data : %d", num, a);
    sleep(1);

    //decrease readcount one by one
    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);

    //if its a last reader 
    if(readcount == 0){
        pthread_mutex_unlock(&wr);
    }

    printf("\n\nReader %ld has left the critical section.", num);
}

void *writer(void *arg){
    long int num = (long int) arg;

    //writer is allowed for writing data so writer lock wr after entering critical section
    pthread_mutex_lock(&wr);

    printf("\n\nWriter %ld is in the critical section now.", num);
    printf("\nWriter %ld is writing data : %d", num, ++a);
    sleep(1);

    //writer release lock of wr after writing 
    pthread_mutex_unlock(&wr);

    printf("\n\nWriter %ld has left the critical section.", num);

}

int main(){
    pthread_t r[10], w[10];
    int nor, now;
    printf("\nEnter number of readers : ");
    scanf("%d", &nor);
    printf("Enter number of writers : ");
    scanf("%d", &now);

    //initializing thread variables
    pthread_mutex_init(&wr, NULL);
    pthread_mutex_init(&mutex, NULL);

    //creating the reader and writer threads
    long int i;
    for(i=0; i<nor; i++){
        pthread_create(&r[i], NULL, reader, (void *)i);
        pthread_join(r[i], NULL);
        pthread_create(&w[i], NULL, writer, (void *)i);
        pthread_join(w[i], NULL);
    }
    // for(i=0; i<now; i++){
    //     pthread_create(&w[i], NULL, writer, (void *)i);
    //     pthread_join(w[i], NULL);
    // }

    //join the reader and writer threads
    // for(i=0; i<nor; i++){
    //     pthread_join(r[i], NULL);
    // }
    // for(i=0; i<now; i++){
    //     pthread_join(w[i], NULL);
    // }

    return 0;
}