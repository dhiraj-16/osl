#include <stdio.h>
#include <stdlib.h>

int i,head,temp_head,finish[100],disc_req[100],tracks,n,min,diff,index,pending,distance = 0;

void SSTF(){
    pending = n;
    distance = 0;
    printf("ENter the head position\n");
    scanf("%d",&head);
    for(int i = 0; i < n; i++){
        finish[i] = 0;
    }
    temp_head = head;
    printf("%d -> ",temp_head);
    while(pending > 0){
        min = 9999;
        for(int i = 0; i < n; i++){
            diff = abs(disc_req[i]-temp_head);
            if(finish[i] == 0 && diff < min){
                min = diff;
                index = i;
                
            }
        }
        finish[index] = 1;
        distance += abs(temp_head-disc_req[index]);
        pending--;
        temp_head = disc_req[index];
        printf("%d -> ",temp_head);
    }
    printf("END\n");
    printf("Ttaol distance is %d : ",distance);
    
    
}
void sort(){
    for(i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(disc_req[j] > disc_req[j+1]){
                int temp = disc_req[j];
                disc_req[j] = disc_req[j+1];
                disc_req[j+1] = temp;
            }
        }
    }
}
void SCAN(){
    printf("Enter the initial head posi\n");
    scanf("%d",&head);
    int dir;
    printf("enter the direction 1- for higher 0 - for lower\n");
    scanf("%d",&dir);
    temp_head = head;
    printf("%d -> ",temp_head);
    sort();
    
    for(i = 0; i <n; i++ ){
        if(head > disc_req[i]){
            
            continue;
        }else{
            break;
        }
    }
    if(dir == 1){
        for(i = index; i< n; i++){
            printf("%d -> ", disc_req[i]);
            distance += abs(temp_head-disc_req[i]);
            temp_head = disc_req[i];
            
        }
        printf("%d -> ",tracks-1);
        distance += abs(disc_req[n-1]-(tracks-1));
        temp_head = tracks-1;
        for(i = index-1; i >= 0; i-- ){
            printf("%d -> ", disc_req[i]);
            distance += abs(temp_head-disc_req[i]);
            temp_head = disc_req[i];
        }
        printf("END\n");
        printf("Ttaol distance is %d : ",distance);
    }else{
        for(i = index-1; i >= 0; i-- ){
            printf("%d -> ", disc_req[i]);
            distance += abs(temp_head-disc_req[i]);
            temp_head = disc_req[i];
        }
        printf("%d -> ",0);
        distance += abs(disc_req[0]-0);
        temp_head = 0;
        for(i = index; i< n; i++){
            printf("%d -> ", disc_req[i]);
            distance += abs(temp_head-disc_req[i]);
            temp_head = disc_req[i];
            
        }
        
        
        printf("END\n");
        printf("Ttaol distance is %d : ",distance);
    }
    
    
}
void CLOOK(){
    
}
int main(){
    printf("enter the number of tracks\n");
    scanf("%d",&tracks);
    printf("Enter the number of request\n");
    scanf("%d",&n);
    
    printf("Enter request seq\n");
    for(i = 0; i < n; i++){
        scanf("%d",&disc_req[i]);
    }
    int ch ;
    while(1){
        printf("Enter 1 for SSTF\n2 for SCAN\n 3 for CLOOK\n");
        scanf("%d",&ch);
        
        switch(ch){
            case 1 : SSTF();
            case 2 : SCAN();
            case 3 : CLOOK();
            case 4 : break;
        }
        
    }
    

}

/*
sstf
input 
100
11
45 21 67 90 4 50 89 52 61 87 25
50
50 -> 50 -> 52 -> 45 -> 61 -> 67 -> 87 -> 89 -> 90 -> 25 -> 21 -> 4 -> END
answ = 140
*/