#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in=0,out=0;
int count=0;
int item_produced=1;

int mutex=1,full=0,empty=BUFFER_SIZE;

void wait(int *s){
    while(*s<=0);
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void producer(){
    wait(&empty);
    wait(&mutex);
    buffer[in]=item_produced;
    printf("Producer has Produced: Item %d\n",item_produced);
    in=(in+1)%BUFFER_SIZE;
    count++;
    item_produced++;
    signal(&mutex);
    signal(&full);
}

void consumer() {
    if (count==0){
        printf("Buffer is Empty\n");
    }
    wait(&full);
    wait(&mutex);
    int item = buffer[out];
    printf("Consumer has Consumed: Item %d\n", item);
    out = (out + 1) % BUFFER_SIZE;
    count--;
    signal(&mutex);
    signal(&empty);
}

void main(){
    int choice;
    do{
        printf("MENU\n1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while(choice!=3);
}