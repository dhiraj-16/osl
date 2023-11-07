#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(){
    int fd1, fd2;
    char *myfifo1 = "file1";
    char *myfifo2 = "file2";
    char str1[100], str2[100], ch;
    FILE *fp;   //file pointer

    //reading data from first pipe
    fd1 = open(myfifo1, O_RDONLY);
    read(fd1, str1, 100);
    printf("\nReading from first pipe : \n%s", str1);
    close(fd1);

    int l=1, w=1, c=0, i=0;
    //counting chars, words, lines
    while(str1[i] != '\0'){
        if(str1[i] == '.' || str1[i] == '\n'){
            l++;
        }
        else if(str1[i] == ' '){
            w++;
        }
        else{
            c++;
        }
        i++;
    }

    printf("\nNumber of Lines : %d", l);
    printf("\nNumber of Words : %d", w);
    printf("\nNumber of Chars : %d\n", c);

    //writing number of lines, words, chars in txt file
    fp = fopen("demo.txt", "w");
    fprintf(fp, "\nNumber of Lines : %d", l);
    fprintf(fp, "\nNumber of Words : %d", w);
    fprintf(fp, "\nNumber of Chars : %d\n", c);
    fclose(fp);

    //again opening txt file for reading (we coping txt file data into str2)
    fp = fopen("demo.txt", "r");
    ch = fgetc(fp);   //it will read char by char from fp
    i = 0;
    while(ch != EOF){
        str2[i] = ch;
        i++;
        ch = fgetc(fp);
    }
    str2[i] = '\0';
    fclose(fp);

    //writing data of txt(currently in str2 now) in second pipe
    fd2 = open(myfifo2, O_WRONLY);
    write(fd2, str2, strlen(str2)+1);
    close(fd2);
}