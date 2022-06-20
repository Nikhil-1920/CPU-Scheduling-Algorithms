// Banker's Algorithm implementation in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <stdio.h>
#include <stdbool.h>

#define totalProcesses 5
#define totalResources 3
#define MAXINT 9999

int available[totalResources] = {3,3,2};
int maxRequest[totalProcesses][totalResources] = {7,5,3,3,2,2,9,0,2,2,2,2,4,3,3};
int allocation[totalProcesses][totalResources] = {0,1,0,2,0,0,3,0,2,2,1,1,0,0,2};
int resrcsNeed[totalProcesses][totalResources] = {7,4,3,1,2,2,6,0,0,0,1,1,4,3,1};

bool Finish[totalProcesses];
int safeSeries[totalProcesses] = {MAXINT, MAXINT, MAXINT, MAXINT, MAXINT};
int request[totalResources];


void displayInfo(void) {
  
  int i, j;
	printf("Current remaining resources: ");
  
	for(j = 0; j < totalResources; j++) { printf("%d ", available[j]); }
		
	printf("\n\n PID\tMax\tAlloc\tNeed\n");
  
	for(i = 0; i < totalProcesses; i++) {
    
	  printf(" P%d\t", i);
		for(j = 0; j < totalResources; j++) {
			printf("%d ", maxRequest[i][j]);
		}
    
		printf("\t");
		for(j = 0; j < totalResources; j++) {
		    printf("%d ", allocation[i][j]);
		}
    
		printf("\t");
		for(j = 0; j < totalResources; j++) {
			printf("%d ", resrcsNeed[i][j]);
		}
		printf("\n");
	}
}


void safeInfo(int *work, int i) {
  
	int j;
  
	printf(" P%d\t", i);
	for(j = 0; j < totalResources; j++) {
		printf("%d ", work[j]);
	}
  
	printf("\t");
	for(j = 0; j < totalResources; j++) {
		printf("%d ", resrcsNeed[i][j]);
	}
  
	printf("\t");
	for (j = 0; j < totalResources; j++) {
		printf("%d ", allocation[i][j]);
	}
  
	printf("\t");
	for (j = 0; j < totalResources; j++) {
		printf("%d ", allocation[i][j] + work[j]);
	}
  
	printf("\n");
}


bool isSafe(void) {
  
	int i, j, k, flag, tempVal1;
	int trueFinished = 0;
	int work[totalResources];

	for(i = 0; i < totalProcesses; i++) { work[i] = available[i]; }
	for(i = 0; i < totalProcesses; i++) { Finish[i] = 0; }
	
	i = 0;
	int tempVal2 = 0;

	while(trueFinished != totalProcesses) {
    
		int j = 0;
		if(Finish[i] != 1) {
      
			for(j = 0; j < totalResources; j++) {
        
				if(resrcsNeed[i][j] > work[j]) { break; }
			}
		}

		if(j == totalResources) {
      
			Finish[i] = 1;
			safeInfo(work, i);
      
			for(k = 0; k < totalResources; k++) {
				work[k] += allocation[i][k];
			}
      
			int k2;
			safeSeries[trueFinished++] = i;
		}

		i++;
		if(i >= totalProcesses) {
      
			if(flag == 0) {
				tempVal2 = trueFinished;
				tempVal1 = trueFinished;
			}
      
			i = i % totalProcesses;
			if(flag == 1) {
        
				tempVal1 = trueFinished;
				if(tempVal2 == tempVal1) { break; }
				else { tempVal1 = tempVal2; }
			}
      
			flag = 1;
		}
    
		tempVal1 = trueFinished;
	}

	if(trueFinished == totalProcesses) {
    
		printf("\nSystem Safe!!\n\nThe safe sequence is: ");
		for(i = 0; i < totalProcesses; i++) {
			printf("%d ", safeSeries[i]);
		}
    
		return true;
	}

	printf("********System Unsafe!!********\n");
	return false;
}


int main(void) {
  
    int i, j, currentProcs;
    int key = 0;

    printf("\nPress any key from 0 to 9: ");
	  scanf("%d", &key);

    printf("\n---------------------------------------------------------\n");
    displayInfo();
    printf("\nSystem Safety Analysis.");
    printf("\n---------------------------------------------------------\n");
    printf(" PID\tWork\tNeed\tAlloc\tWork+Allocation\n");
    isSafe();
  
    while(true) { 
      
      printf("\n---------------------------------------------------------\n");
      printf("\nEnter the process to allocate. (Enter 999 to exit.) ");
      scanf("%d", &currentProcs);
      printf("\nEnter resources to allocate to process P%d: ", currentProcs);
      
      if(currentProcs == 999) { break; }
        
      for(j = 0; j < totalResources; j++) { 
        scanf("%d", &request[j]); 
      }

		  for(j = 0; j < totalResources; j++) {
        
        if(request[j] <= resrcsNeed[currentProcs][j]) { continue; }   
        
        else { 
          printf("ERROR!\n"); 
          break; 
        }
	    }

      if(j == totalResources) {

        for(j = 0; j < totalResources; j++) {

          if(request[j] <= resrcsNeed[currentProcs][j]) { continue; } 
          else { 
            printf("Insufficient Resources, Waiting!\n"); 
           `break; 
          }
        }

			  if(j == totalResources) {
        
          for(j = 0; j < totalResources; j++) {

            available[j] -= request[j];
            allocation[currentProcs][j] += request[j];
            resrcsNeed[currentProcs][j] -= request[j];
          }

          printf("\nSystem Safety Analysis.");
          printf("\n---------------------------------------------------------\n");
          printf(" PID\tWork\tNeed\tAlloc\tWork+Allocation\n");

          if(isSafe()) {

            printf("Allocation Success!\n");
            displayInfo();
          }

          else {

            for(j = 0; j < totalResources; j++) {

              available[j] += request[j];
              allocation[currentProcs][j] -= request[j];
              resrcsNeed[currentProcs][j] += request[j];
            }

            printf("Allocation Failed!\n");
            displayInfo();
          }
			  }
		  }
    }
  
    printf("\n\n");
    return 0;
}
