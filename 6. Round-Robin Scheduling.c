
// Round-Robin (RR) CPU scheduling algorithms implementation in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <stdio.h>

int main(void) {
  
    int totalProcs, procNum[20], remBurstTime[20];
    int arrivalTime[20], burstTime[20], waitTime = 0;
    int timeQuantum, totalPerformanceTime = 0, status = 0;
    int totalWaitTime = 0, totalturnAroundTime = 0;
    int i, remainingProcs = 0, turnAroundTime = 0;
    double avgWaitTime = 0, avgturnAroundTime = 0;

    printf("\nEnter the total number of processes: ");
    scanf("%d", &totalProcs);

    remainingProcs = totalProcs;
    printf("\nEnter the arrival time and burst time of each process.\n");

    for(i = 0; i < totalProcs; i++) {
      
        printf("\nProcess[%d]\n", i + 1);
        printf("What is arrival time(in ms)? ");
        scanf("%d", &arrivalTime[i]);
        printf("What is burst time(in ms)? ");
        scanf("%d", &burstTime[i]);
        procNum[i] = i + 1;
        remBurstTime[i] = burstTime[i];
    }

    printf("\nEnter time quantum(in ms): ");
    scanf("%d", &timeQuantum);
    
    printf("\n");
    printf("-------------------------------------------------------------------------------");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------------------------------------");
    
    for(totalPerformanceTime = 0, i = 0; remainingProcs != 0; ) {

        if(remBurstTime[i] <= timeQuantum && remBurstTime[i] > 0) {
          
            totalPerformanceTime += remBurstTime[i];
            remBurstTime[i] = 0;
            status = 1;
        }

        else if(remBurstTime[i] > 0) {
          
            remBurstTime[i] -= timeQuantum;
            totalPerformanceTime += timeQuantum;
        }
    
        if(status == 1 && remBurstTime[i] == 0) {
          
            remainingProcs--;
            waitTime = totalPerformanceTime - arrivalTime[i] - burstTime[i];
            turnAroundTime = totalPerformanceTime - arrivalTime[i];

            printf("\nProcess[%d]\t%d\t\t%d\t\t%d\t\t%d", procNum[i], arrivalTime[i], burstTime[i], waitTime, turnAroundTime);
            totalWaitTime += totalPerformanceTime - arrivalTime[i] - burstTime[i];
            totalturnAroundTime += totalPerformanceTime - arrivalTime[i];
            status = 0;
        }

        if(i == totalProcs - 1) { i = 0; }
      
        else if(arrivalTime[i + 1] <= totalPerformanceTime) {
            i++;
        }
      
        else i = 0;
    }

    avgWaitTime = totalWaitTime * 1.0 / totalProcs; 
    avgturnAroundTime = totalturnAroundTime * 1.0 / totalProcs; 

    printf("\n");
    printf("-------------------------------------------------------------------------------");
    printf("\n\nAverage Waiting Time = %.1lfms", avgWaitTime);
    printf("\nAverage Turnaround Time = %.1lfms\n\n", avgturnAroundTime);
    return 0;
}
