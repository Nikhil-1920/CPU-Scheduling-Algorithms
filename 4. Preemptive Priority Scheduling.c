// Preemptive CPU scheduling algorithms implementation in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <stdio.h>

int main(void) {

    int totalProcs, procNum[20], procPriority[20];
    int arrivalTime[20], burstTime[20], waitTime[20];
    int turnAroundTime[20], completionTime[20], procEnd;
    int i, j, tempVal[20], count = 0, smallest = 0;
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    double avgWaitTime = 0, avgTurnAroundTime = 0;

    printf("\nEnter the total number of processes: ");
    scanf("%d", &totalProcs);

    printf("\nEnter the priority, arrival time and burst time of each process.\n");

    for(i = 0; i < totalProcs; i++) {
      
        printf("\nProcess[%d]\n", i + 1);
        printf("What is process priority? ");
        scanf("%d", &procPriority[i]);
        printf("What is arrival time(in ms)? ");
        scanf("%d", &arrivalTime[i]);
        printf("What is burst time(in ms)? ");
        scanf("%d", &burstTime[i]);
        procNum[i] = i + 1;
    }
    
    for(i = 0; i < totalProcs; i++) { tempVal[i] = burstTime[i]; }
     
    procPriority[19] = -1;
    for(j = 0; count != totalProcs; ++j) {
      
        smallest = 19;
        for(i = 0; i < totalProcs; ++i) {
          
            if(arrivalTime[i] <= j && procPriority[i] > procPriority[smallest] && burstTime[i] > 0) { smallest = i; }
        }

        burstTime[smallest]--;

        if(burstTime[smallest] == 0) {
          
            ++count;
            procEnd = j + 1;
            completionTime[smallest] = procEnd;
            waitTime[smallest] = procEnd - arrivalTime[smallest] - tempVal[smallest];
            turnAroundTime[smallest] = procEnd - arrivalTime[smallest];
        }
    }

    printf("\n");
    printf("-----------------------------------------------------------------------------------------------");
    printf("\nProcess ID\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-----------------------------------------------------------------------------------------------");
    
    for(i = 0; i < totalProcs; ++i) {
      
        printf("\nProcess[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d", procNum[i], procPriority[i], arrivalTime[i], tempVal[i], waitTime[i], turnAroundTime[i]);
        totalWaitTime += waitTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // average waiting time
    avgWaitTime = (double)totalWaitTime / totalProcs; 

    // average turnaround time 
    avgTurnAroundTime = (double)totalTurnAroundTime / totalProcs;
    printf("\n-----------------------------------------------------------------------------------------------");
    printf("\n\nAverage Waiting Time = %.1lfms", avgWaitTime);
    printf("\nAverage Turnaround Time = %.1lfms\n\n", avgTurnAroundTime);
    return 0;
}
