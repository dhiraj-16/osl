#include<stdlib.h>
#include<stdio.h>

int finish[10], pn[10], bt[10], at[10], tat[10], wt[10], rbt[10];    //pn - process name, rbt - remaining burst time
int time, count, n, choice, pending; 
//func 1
void input(){

    printf("Enter Number of processes : ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        pn[i] = i;

        //at input
        printf("\nEnter arrival time for process P%d : ", pn[i]);
        scanf("%d", &at[i]);

        //bt input
        printf("\nEnter burst time for process P%d : ", pn[i]);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }
}

//func 2
void menu(){
    printf("\n\n\n*****MENU*****");
    printf("\n1. Round Robin");
    printf("\n2. SJF Preemptive");
    printf("\n3. Exit");

    printf("\nEnter your choice : ");
    scanf("%d", &choice);
}

//func 3
void output(){
    printf("\n\nProcess  A.T.  B.T.  W.T  T.A.T");
    for(int i=0; i<n; i++){
        printf("\n P%d \t %d \t %d \t %d \t %d", pn[i], at[i], bt[i], wt[i], tat[i]);
    }

    int sum = 0;
    for(int i=0; i<n; i++){
        sum += tat[i];
    }
    float avgtat = (float)sum/n;
    printf("\n Average TAT : %.5f", avgtat);

    int sum2 = 0;
    for(int i=0; i<n; i++){
        sum2 += wt[i];
    }
    float avgwt = (float)sum2/n;
    printf("\n Average WT : %.5f", avgwt);
}

//func 5
void sort(){
    //whole swapping 
    int t;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(rbt[i] < rbt[j]){
                t = rbt[i];
                rbt[i] = rbt[j];
                rbt[j] = t;

                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;

                t = at[i];
                at[i] = at[j];
                at[j] = t;

                t = finish[i];
                finish[i] = finish[j];
                finish[j] = t;

                t = pn[i];
                pn[i] = pn[j];
                pn[j] = t;
            }
        }
    }
}

//func 6
//SJF PREEMTIVE
void sjf(){
    input();

    pending = n;    //all process are pending initially 
    printf("\n Gantt Chart ==> ");

    //initialize finish and waiting time 
    for(int i=0; i<n; i++){
        finish[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    for(time = 0, count = 0; pending > 0;){
        sort();
        for(count=0; count < n; count++){
            if(finish[count] == 0 && at[count] <= time){
                //gantt chart 
                printf("P%d ", pn[count]);
                //increase time by 1
                time += 1;
                //decrease rbt by 1
                rbt[count] -= 1;

                //consider if the process is finished
                if(rbt[count] == 0){
                    finish[count] = 1;
                    pending--;
                    tat[count] = time - at[count];
                    wt[count] = tat[count]-bt[count];
                    
                }
                break;
            }
        }
    }
    output();
}

int main(){
    while(1){
        menu();
        switch(choice){


            case 2: sjf();
            break;

            case 3: exit(0);
            break;
        }
    }
    return 0;
}

//round robin
/*
#include<stdio.h>

 
int main()
{
 
  int cnt,j,n,t,remain,flag=0,tq;
  int wt=0,tat=0,at[10],bt[10],rt[10];
  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(cnt=0;cnt<n;cnt++)
  {
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",cnt+1);
    scanf("%d",&at[cnt]);
    scanf("%d",&bt[cnt]);
    rt[cnt]=bt[cnt];
  }
  printf("Enter Time Quantum:\t");
  scanf("%d",&tq);
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(t=0,cnt=0;remain!=0;)
  {
    if(rt[cnt]<=tq && rt[cnt]>0)
    {   
      t+=rt[cnt];
      rt[cnt]=0;
      flag=1;
    }
    else if(rt[cnt]>0)
    {
        //  printf("P %d -> ",cnt+1);
      rt[cnt]-=tq;
      t+=tq;
    }
    if(rt[cnt]==0 && flag==1)
    {   
        // printf("P %d -> ",cnt+1);
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",cnt+1,t-at[cnt],t-at[cnt]-bt[cnt]);
      wt+=t-at[cnt]-bt[cnt];
      tat+=t-at[cnt];
      flag=0;
    }
    if(cnt==n-1)
      cnt=0;
    else if(at[cnt+1]<=t)
      cnt++;
    else
      cnt=0;
  }
  printf("\nAverage Waiting Time= %f\n",wt*1.0/n);
  printf("Avg Turnaround Time = %f",tat*1.0/n);
  
  return 0;
}

*/
