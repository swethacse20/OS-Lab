//SJF when AT is 0
#include<stdio.h>

int n , w_t[100] , t_a_t[100] , b_t[100] , p[100];
float w_t_avg = 0 , t_a_t_avg = 0;

sortByBurstTimes(){
int i,j,temp=0;
for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
        if (b_t[i]>b_t[j]){
            temp = b_t[i];
            b_t[i] = b_t[j];
            b_t[j] = temp;

            temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
    }
}
}

findTurnAroundTime(){
    int i;
    for(i=0;i<n;i++){
        t_a_t[i] = b_t[i] + w_t[i];
        t_a_t_avg += t_a_t[i];
    }
    t_a_t_avg /= n;
}

findWaitingTime(){
    int i;
    w_t[0]=0;
    for(i=1;i<n;i++){
        w_t[i] = b_t[i-1] + w_t[i-1];
        w_t_avg += w_t[i];
    }
     w_t_avg /= n;
}

findAvgTime(){
int i;
findWaitingTime();
findTurnAroundTime();
printf("PROCESS      BURST TIME      WAITING TIME        TURN AROUND TIME\n");
for(i=0;i<n;i++){
    printf("%5d         %5d         %5d         %5d\n",i+1,b_t[i],w_t[i],t_a_t[i]);
}
printf("\n Average waiting time = %f",w_t_avg);
printf("\n Average Turn Around Time = %f",t_a_t_avg);
}

int main(){
    int i;
    printf("enter number of processes : ");
    scanf("%d",&n);
    printf("Enter burst times for the process : \n");
    for (i=0;i<n;i++){
        p[i]=i+1;
        printf(" BT for process %d : ",p[i]);
        scanf("%d",&b_t[i]);
    }

    sortByBurstTimes();
    findAvgTime();

}
