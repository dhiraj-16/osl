// main.c 
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

//print array function 
void printArray(int arr[], int n){
    printf("\n [ ");
    for(int i=0; i<n; i++){
        printf(" %d, ", arr[i]);
    }
    printf(" ] \n");
}

//sort function 
void bubblesort(int arr[],int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){

    //Main Process Starts
    printf("\n This is Main Process. ");
    printf("\n PID : %d | PPID : %d ", getpid(), getppid());

    //size of array 
    int n;
    printf("\n Enter size of an array : ");
    scanf("%d", &n);

    //declaring and inputting array
    int arr[n];
    printf("\nEnter %d integers : ", n);
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    //printing entered array 
    printf("\n Enterred Array : ");
    printArray(arr, n);



    //calling fork system call
    pid_t child = fork();  

    if(child < 0){
        printf("\n Fork Failed.");
        exit(1);
    }
    else if(child == 0){

        //Inside the Child Process
        //1
        wait(NULL);
        sleep(1);
        char *args[n+2];
        args[0] = "./child";    //child2b.c ka output file name pass karo
        
        for(int i=0; i<n; i++){
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", arr[i]);   //conveting int to string format and pass them into the buffer
            args[i+1] = strdup(buffer);    //creates new copy of the string 
        }
        args[n+1] = NULL;  //indicating end of list 

        //2
        execve(args[0], args, NULL);
        perror("execve failed");

        //3
        printf("\n Main Process ends with PID : %d", getpid());
        return 1;
    }
    else{
        //Inside Parent Process
        // wait(NULL);
        printf("\n Parent Process started sorting.\n");
        bubblesort(arr,n);
        printArray(arr,n);
        // printf("\nPID : %d  |  Child PID : %d ", getpid(), child);
        printf("\n");
        // wait(NULL);

        // printf("\n\n Parent Process Executed Completely.\n\n");
        return 0;
    }
}




// child.c file is 
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    printf("\nChild.c process started.");
    // printf("\nPID: %d", getpid());
    
    printf("\n\nREVERSED ARRAY:");
    
    printf("\n[%s,", argv[argc - 1]);
    for (int i = argc - 2; i > 1; i--)
    {
        printf(" %s,", argv[i]);
    } 
    printf(" %s]", argv[1]);
    printf("\n");

    return 0;
}

*/