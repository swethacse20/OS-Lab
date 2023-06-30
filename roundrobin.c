#include<stdio.h>>
int n , w_t[100] , t_a_t[100] , b_t[100] , quantum;
float w_t_avg = 0 , t_a_t_avg = 0;

findWaitingTime(){
int temp[100],t=0,i,flag;
for(i=0;i<n;i++){
    temp[i]=b_t[i];
}
while(1){
    flag =1;
    for(i=0;i<n;i++){
        if(temp[i]>0){
            flag = 0 ;
            if(temp[i]>quantum){
                t += quantum;
                temp[i] -= quantum;
            }
            else{
                t += temp[i];
                w_t[i] = t - b_t[i];
                w_t_avg += w_t[i];
                temp[i] = 0;
            }
        }
    }
    if(flag == 1){
        w_t_avg /= n;
        break;
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

findAvgTime(){
int i;
findWaitingTime();
findTurnAroundTime();
printf("PROCESS     BRUST TIME      WAITING TIME        TURN AROUND TIME\n");
for(i=0;i<n;i++){
    printf("%5d         %5d         %5d         %5d\n",i+1,b_t[i],w_t[i],t_a_t[i]);
}
printf("\n Average waiting time = %f",w_t_avg);
printf("\n Average Turn Around Time = %f",t_a_t_avg);
}


int main(){
int i;
printf("Enter number of processes : ");
scanf("%d",&n);
printf("Enter the burst times : \n");
for(i=0;i<n;i++){
    printf("BT for process %d : ",i+1);
    scanf("%d",&b_t[i]);
}
printf("enter time Quantum/slice : ");
scanf("%d",&quantum);
findAvgTime();
}