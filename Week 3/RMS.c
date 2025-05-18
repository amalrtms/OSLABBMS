#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int id;
    int period;
    int execution_time;
    int remaining_time;
    int next_start_time;
}Task;

void sort_by_priority(Task tasks[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(tasks[j].period>tasks[j+1].period){
                Task temp=tasks[j];
                tasks[j]=tasks[j+1];
                tasks[j+1]=temp;
            }
        }
    }
}

void rms_scheduling(Task tasks[],int n,int total_time){
    sort_by_priority(tasks,n);

    for(int t=0;t<total_time;t++){
        for(int i=0;i<n;i++){
            if(t%tasks[i].period==0){
                tasks[i].remaining_time=tasks[i].execution_time;
            }
        }

        int executed=0;
        for(int i=0;i<n;i++){
            if(tasks[i].remaining_time>0){
                printf("Time %d: Executing T%d\n",t,tasks[i].id);
                tasks[i].remaining_time--;
                executed=1;
                break;
            }
        }

        if(!executed){
            printf("Time %d: Idle\n",t);
        }
    }
}

int main(){
    Task tasks[MAX];
    int num_tasks,total_time;
    printf("Enter number of tasks: ");
    scanf("%d",&num_tasks);
    if(num_tasks>MAX||num_tasks<=0){
        printf("Error: Invalid number of tasks.\n");
        return 1;
    }
    for(int i=0;i<num_tasks;i++){
        printf("Enter period and execution time for Task %d: ",i+1);
        tasks[i].id=i+1;
        scanf("%d %d",&tasks[i].period,&tasks[i].execution_time);
        tasks[i].remaining_time=0;
    }
    printf("Enter total simulation time: ");
    scanf("%d",&total_time);
    rms_scheduling(tasks,num_tasks,total_time);
    return 0;
}