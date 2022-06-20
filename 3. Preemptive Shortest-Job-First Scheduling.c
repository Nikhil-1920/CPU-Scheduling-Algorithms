// Preemptive Shortest-Job-First(SJF) CPU scheduling algorithms implementation in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <stdio.h>
#define MAXPROC 20

int main(void) {
  
    int i, totalProcs, process[MAXPROC][7], totalBtAllProcs = 0;
    int firstArrived = 0, tempVal[MAXPROC], totalBTime = 0;
    int totalWaitTime = 0, totalTurnAroundTime = 0;
	  float avgWaitTime = 0, avgTurnAroundTime = 0;

    printf("\nEnter the total number of processes: ");
    scanf("%d", &totalProcs);

    printf("\nEnter process id, arrival time and burst time.\n");

    for(i = 0; i < totalProcs; i++) {

      printf("\nEnter process id: P");
      scanf("%d", &process[i][0]);
      printf("Enter arrival time(in ms): ");
      scanf("%d", &process[i][1]);
      printf("Enter burst time(in ms): ");
      scanf("%d", &process[i][2]);
      totalBtAllProcs += process[i][2];
      process[i][6] = -1;
    }

    firstArrived = process[0][1];
  
    for(i = 0; i < totalProcs; i++) {
      
      if(firstArrived > process[i][1]) { firstArrived = process[i][1]; }
      
      // storing burst time in tempVal[]
      tempVal[i] = process[i][2];
    }
	
    totalBTime = firstArrived;
    totalBtAllProcs += firstArrived;
    while(totalBTime < totalBtAllProcs) {
      
      for(i = 0; i < totalProcs; i++) {
        
        if(process[i][6] == -1 && process[i][1] <= totalBTime) {
          firstArrived = i;
          break;
        }
      }	

      for(i = 0; i < totalProcs; i++) {

        if(process[i][6] == -1 && process[i][1] <= totalBTime) {
          if(process[firstArrived][2] > process[i][2]) { firstArrived = i; }
      }

      ++totalBTime;
      --process[firstArrived][2];

      // process is fully processed
      if(process[firstArrived][2] == 0) { 
        
        process[firstArrived][6] = 0; 
        // completion time of the process
        process[firstArrived][3] = totalBTime;	
      }	
    }

	  printf("\n--------------------------------------------------------------------------------------------");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
    printf("\n--------------------------------------------------------------------------------------------");

    for(i = 0; i < totalProcs; i++) {

      printf("\nP%d", process[i][0]);
      printf("\t\t%d", process[i][1]);
      printf("\t\t%d", tempVal[i]);
      printf("\t\t%d", process[i][3]);
      process[i][4] = process[i][3] - process[i][1];		
      printf("\t\t%d", process[i][4]);
      process[i][5] = process[i][4] - tempVal[i];
      printf("\t\t%d", process[i][5]);
      totalWaitTime += process[i][5];		
      totalTurnAroundTime += process[i][4];	
    }

    avgWaitTime = (float)totalWaitTime / totalProcs;
    avgTurnAroundTime = (float)totalTurnAroundTime / totalProcs;
      
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("\nAverage Waiting Time: %.2fms", avgWaitTime);
    printf("\nAverage Turnaround Time: %.2fms\n\n", avgTurnAroundTime);
    return 0;
}
