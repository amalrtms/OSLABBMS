#include <stdio.h>
#include <stdlib.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
int semaphore[N];
int forks[N]={0};
int hungry[N]={0};

int left(int i) {
    return (i+N-1)%N;
}

int right(int i) {
    return (i+1)%N;
}

void wait(int *S) {
    while (*S<=0);
    *S=*S-1;
}

void signal(int *S) {
    *S=*S+1;
}

void test(int i) {
    if (state[i]==HUNGRY &&
        state[left(i)]!=EATING &&
        state[right(i)]!=EATING) {
        state[i]=EATING;
        signal(&semaphore[i]);
    }
}

void take_forks(int i) {
    state[i]=HUNGRY;
    printf("P %d is HUNGRY and trying to eat\n",i+1);
    test(i);
    wait(&semaphore[i]);
}

void put_forks(int i) {
    state[i]=THINKING;
    printf("P %d has finished eating and is now THINKING\n",i+1);
    test(left(i));
    test(right(i));
}

void simulate(int max_eaters) {
    int eating_count=0;
    for (int i=0; i<N && eating_count<max_eaters; i++) {
        if (hungry[i]) {
            printf("P %d is waiting\n",i+1);
        }
    }
    for (int i=0; i<N && eating_count<max_eaters; i++) {
        if (hungry[i] && state[i]==HUNGRY) {
            take_forks(i);
            if (state[i]==EATING) {
                printf("P %d is granted to eat\n",i+1);
                hungry[i]=0;
                eating_count++;
                put_forks(i);
            }
        }
    }
}

int main() {
    int total, hungry_count, id, choice;
    for (int i=0; i<N; i++) {
        state[i]=THINKING;
        semaphore[i]=0;
    }
    printf("Total number of philosophers: ");
    scanf("%d",&total);
    printf("How many are hungry: ");
    scanf("%d",&hungry_count);
    for (int i=0; i<hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ",i+1,total);
        scanf("%d",&id);
        hungry[id-1]=1;
        state[id-1]=HUNGRY;
    }
    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if (choice==3)
            break;
        if (choice==1 || choice==2) {
            simulate(choice);
        } else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}