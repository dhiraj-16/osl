

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
 
// Function to print an Array 
void printArray(int arr[], int n) 
{ 
    printf("\n[");
    for(int i=0; i<n; i++){
        printf(" %d ",arr[i]);
    }
    printf(" ]");
} 
 
// Bubble Sort 
void bubbleSort(int arr[], int n) 
{ 
    int temp, i, j; 
    for (i = 0; i < n - 1; i++) 
    {  
        for (j = 0; j < n - i - 1; j++) 
        { 
            if (arr[j] > arr[j + 1]) 
            { 
                temp = arr[j]; 
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp; 
            } 
        } 
    } 
} 
 

int main() 
{ 
    // Variable declarations 
    int n, i, choice; 
 
    // Main process starts 
    printf("\nThis is the main process."); 
    printf("\nPID: %d", getpid()); 
    printf(" | PPID: %d", getppid()); 
 
    printf("\n\nEnter the number of integers to sort: "); 
    scanf("%d", &n); 
    int arr[n]; 
    printf("Enter the %d integers: ", n); 
    for (int i = 0; i < n; i++) 
    { 
        scanf("%d", &arr[i]); 
    } 
 
    printf("\nENTERED ARRAY:"); 
    printArray(arr, n); 
 
    printf("\n\n-------- MENU --------\n"); 
    printf("1 - Normal Execution (Fork & Wait)\n"); 
    printf("2 - Orphan Process\n"); 
    printf("3 - Zombie Process\n"); 
    printf("\nEnter your choice: "); 
    scanf("%d", &choice); 
 
    switch (choice) 
    { 
    case 1: 
    { 
        pid_t pid = fork(); 
 
        if (pid < 0) 
        { 
            // Failed Fork 
            printf("Fork failed.\n"); 
            exit(1); 
        } 
        else if (pid == 0) 
        { 
            // Inside Child Process 
            printf("\nChild process (Bubble Sort) started."); 
            printf("\nPID: %d", getpid()); 
            printf("\nPPID: %d\n", getppid()); 
            bubbleSort(arr, n); 
 
            printf("\nSorted array by the child process (Bubble Sort):"); 
            printArray(arr, n); 
 
            printf("\nChild process executed successfully.\n"); 
        } 
        else 
        { 
            // Inside Parent Process 
            printf("\nParent process (Quick Sort) started.\nIt'll wait for the child process to complete."); 
            printf("\nPID: %d", getpid()); 
             
            wait(NULL); 
 
            printf("\n\nSorted array by the parent process (Quick Sort):"); 
            bubbleSort(arr, n); 
            printArray(arr, n); 
 
            printf("\n\nChild process has completed. This is the parent process."); 
            printf("\nParent process executed successfully."); 
        } 
        break; 
    } 
    case 2: 
    { 
        pid_t p;
        p = fork();

        if(p < 0){
            printf("Fork failed\n");
        }else if(p == 0){
            //child process
            sleep(2);
            printf("This is child (orphan) process run id is %d\n", getpid());
            printf("This is parent process id is %d\n", getppid());
        }else{
            //parent process
            printf("This is parent process run id is %d\n", getpid());
            printf("This is parent my child process id is %d\n", p);
        }
        break; 
    } 
    case 3: 
    { 
        pid_t p;
        p = fork();
        if(p < 0){
            printf("FOrk failed\n");
        }else if(p == 0){
            printf("This is child process run id is %d\n", getpid());
            printf("This is parent process id is %d\n", getppid());
        }else{
            //parent process
            sleep(3);
            printf("This is parent (zombie) process run id is %d\n", getpid());
            printf("This is parent my child process id is %d\n", p);
        }
        break; 
    } 
    default: 
        printf("Invalid choice.\n"); 
        break; 
    } 
 
    return 0; 
}


/*
to execute this zombie (child is completed and terminated but still has entry in process table)
$    gcc orphan.c
 $   ./a.out &
 $   ps
then you will see <defunct> i.e it is zombie
how to avoid :
to avoid we will add wait(NULL) line before sleep so that it wait for child status to terminate 
from process table
*/