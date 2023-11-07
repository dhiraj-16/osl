#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

int main(){
    //unique key generate to access shared memory
    key_t key = ftok("shmfile", 65);  //parameters should be same as in writer

    //shmget - return identifier of shared memory into shmid
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    //shmat - attach process to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);
     
    printf("\nReading data from shared memory\n");
    printf("\nData read from shared memory : %s\n", str);

    //shmdt - detach shared memory from process
    shmdt(str);

    //shmctl - destroying shared memory 
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}