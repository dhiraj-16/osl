#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(){
    char *myfifo1 = "file1";
    char *myfifo2 = "file2";
    char str1[100], str2[100];
    int fd1, fd2;

    //Creating FIFO pipes(files)
    fd1 = mkfifo(myfifo1, 0666);
    fd2 = mkfifo(myfifo2, 0666);

    //reading data for writing into first pipe
    printf("\nEnter a string :: ");
    fgets(str1, 100, stdin);

    //writing data on first pipe
    fd1 = open(myfifo1, O_WRONLY);
    write(fd1, str1, strlen(str1)+1);
    close(fd1);

    //Reading data from second pipe
    fd2 = open(myfifo2, O_RDONLY);
    read(fd2, str2, 100);
    //print output
    printf("\n\n Reading data of PIPE2 :: \n%s", str2);
    close(fd2);

}
