#include <stdio.h>
#include <stdlib.h>

void firstFit(int blockSize[],int blocks,int processSize[],int processes){
    int allocation[processes];
    for(int i=0;i<processes;i++){
            allocation[i]=-1;
    }
    for(int i=0;i<processes;i++){
        for(int j=0;j<blocks;j++){
            if(blockSize[j]>=processSize[i]){
                allocation[i]=j;
                blockSize[j]-=processSize[i];
                break;
            }
        }
    }
    printf("\nFirst-Fit:\n");
    for(int i=0;i<processes;i++){
        if(allocation[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
    }
}

void bestFit(int blockSize[],int blocks,int processSize[],int processes){
    int allocation[processes];
    for(int i=0;i<processes;i++) allocation[i]=-1;
    for(int i=0;i<processes;i++){
        int bestIdx=-1;
        for(int j=0;j<blocks;j++){
            if(blockSize[j]>=processSize[i]){
                if(bestIdx==-1 || blockSize[j]<blockSize[bestIdx])
                    bestIdx=j;
            }
        }
        if(bestIdx!=-1){
            allocation[i]=bestIdx;
            blockSize[bestIdx]-=processSize[i];
        }
    }
    printf("\nBest-Fit:\n");
    for(int i=0;i<processes;i++){
        if(allocation[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
    }
}

void worstFit(int blockSize[],int blocks,int processSize[],int processes){
    int allocation[processes];
    for(int i=0;i<processes;i++) allocation[i]=-1;
    for(int i=0;i<processes;i++){
        int worstIdx=-1;
        for(int j=0;j<blocks;j++){
            if(blockSize[j]>=processSize[i]){
                if(worstIdx==-1 || blockSize[j]>blockSize[worstIdx])
                    worstIdx=j;
            }
        }
        if(worstIdx!=-1){
            allocation[i]=worstIdx;
            blockSize[worstIdx]-=processSize[i];
        }
    }
    printf("\nWorst-Fit:\n");
    for(int i=0;i<processes;i++){
        if(allocation[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
    }
}

void main(){
    int blocks,processes;
    int originalBlocks[100],blockCopy[100],processSize[100];
    printf("Enter no of memory blocks: ");
    scanf("%d",&blocks);
    printf("Enter block sizes:\n");
    for(int i=0;i<blocks;i++){
        scanf("%d",&originalBlocks[i]);
    }
    printf("Enter no of processes: ");
    scanf("%d",&processes);
    printf("Enter each process size:\n");
    for(int i=0;i<processes;i++){
        scanf("%d",&processSize[i]);
    }
    for(int i=0;i<blocks;i++){
        blockCopy[i]=originalBlocks[i];
    }
    firstFit(blockCopy,blocks,processSize,processes);
    for(int i=0;i<blocks;i++){
        blockCopy[i]=originalBlocks[i];
    }
    bestFit(blockCopy,blocks,processSize,processes);
    for(int i=0;i<blocks;i++){
        blockCopy[i]=originalBlocks[i];
    }
    worstFit(blockCopy,blocks,processSize,processes);
}