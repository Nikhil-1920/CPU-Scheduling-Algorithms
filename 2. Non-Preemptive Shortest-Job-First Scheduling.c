// Non-Preemptive Shortest-Job-First(SJF) CPU scheduling algorithms implementation in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <stdio.h>

int main(void) {
  
    int totalProcs, tempVal1 = 0, tempVal2 = 0;
  
    printf("\nEnter number of processes: ");
    scanf("%d", &totalProcs);
  
    int i, process[totalProcs][4], time = 0, LOC = 0, found = 0;
    float priority[totalProcs], avgWaitTime = 0, avgTurnAroundTime = 0; 
  
    printf("Enter burst time and arrival time for each process (in same order): ");
  
    for(i = 0; i < totalProcs; i++) {
      
        printf("Process[%d]: ", i++);
        here:
            scanf("%d %d", &process[i][0], &process[i][1]);
            process[i][2] = 0;
      
            if(process[i][0] < 0) {
              
                printf("\nNegative values are not allowed.\n");
                goto here;
            }
      
            if(process[i][1] < 0) {
              
                printf("\nNegative values are not allowed.\n");
                goto here;
            }
      
            if(i == 0) { time = process[i][1]; }
              
            else {
              
                if(process[i][1] < time) { time = process[i][1]; }
            }
    }

    printf("\n-------------------------------------------------------------------------------");
    printf("\nProcess ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time");
    printf("\n-------------------------------------------------------------------------------\n");
  
    while(1) {
      
        found = 0;
        for(i = 0; i < totalProcs; i++) {
          
            if(process[i][2] == 0) {
              
                priority[i] = -100000000.0;
                if(found != 2) { found = 1; }
              
                if(time - process[i][1] >= 0) {
                  
                    found = 2;
                    process[i][3] = time - process[i][1];
                  
                    // priority[i] = ((float)process[i][3] / (float)process[i][0]) - (float)(process[i][0]);
                    priority[i] = ((float)process[i][3] / (float)process[i][0]);
                  
                    if(priority[i] == priority[LOC]) {
                      
                        if(i != LOC) {
                          
                            tempVal1 = priority[LOC];
                            priority[i] = -1 * (float)(process[i][0]);
                            priority[LOC] = -1 * (float)(process[LOC][0]);
                        }
                    }

                    if(priority[i] == tempVal1) { priority[i] = -1 * (float)(process[i][0]); }
                    if(priority[i] > priority[LOC]) { LOC = i; }            
                }
            }
        }

        if(found == 1) {
          
            time -= process[LOC][0];
            if(time == process[0][1]) { time = process[1][1]; } 
            else { time = process[0][1]; }
               
            for(i = 0; i < totalProcs; i++) {
              
                if(process[i][2] == 0) {
                    if(process[i][1] < time) { time = process[i][1]; }
                }
            }
        }

        else if(found == 0) { break; } 

        else if(found == 2) {
          
            printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", LOC + 1, process[LOC][0], process[LOC][1], process[LOC][3], process[LOC][0] + process[LOC][3]);
            time += process[LOC][0];
            process[LOC][2] = 1;
            priority[LOC] = -100000000.0;
        } 
    }

    for(i = 0; i < totalProcs; i++){
      
        tempVal1 += process[i][3];
        tempVal2 += process[i][0] + process[i][3];
    }

    avgWaitTime = (float)tempVal1 / (float)totalProcs;
    avgTurnAroundTime = (float)tempVal2 / (float)totalProcs;

    printf("\nAverage Waiting Time: %.2f", avgWaitTime);
    printf("\nAverage Turnaround Time: %.2f", avgTurnAroundTime);
    printf("\n-------------------------------------------------------------------------------\n\n");
    return 0;
}
