// Implementing Producer-Consumer problem using semaphores in C

// Author: Nikhil Singh
// Last Modified: 20/06/2022


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

int *buffer, bufPosition = -1, bufLength = 0;
int producersCount, consumersCount;
pthread_t *producerThread, *consumerThread;
sem_t buffMutex, emptyCount, fillCount;


// pthread_t self is used for getting id of current thread
int Produce(pthread_t self) {
  
    int i = 0;
    // taking any number between 0 and 50
    int randProduce = 1 + rand() % 50; 
  
    while(!pthread_equal(*(producerThread + i), self) && i < producersCount) {  i++; } 
    printf("\nProducer[%d] produced: %d", i + 1, randProduce);
    return randProduce;
}
    

// sem_wait() locks the semaphore 
// sem_post() unlocks the semaphore
void *Producer() {
  
    while(1) {
      
        int x = Produce(pthread_self());
        sem_wait(&emptyCount);
        sem_wait(&buffMutex);
        ++bufPosition;
        *(buffer + bufPosition) = x;
        sem_post(&buffMutex);
        sem_post(&fillCount);
    }
}


// pthread_equal compares two thread whether equal or not
void Consume(int produceConsumed, pthread_t self) {

    int i = 0;
    while(!pthread_equal(*(consumerThread + i), self) && i < consumersCount) {  i++; }
	   
    printf("\nBuffer: ");
    for(i = 0; i <= bufPosition; ++i) { printf("%d ", *(buffer + i)); }  
    printf("\nConsumer[%d] consumed: %d\nCurrent buffer length: %d\n", i + 1, produceConsumed, bufPosition);
	  printf("\n---------------------------------------\n");
}


void *Consumer() {
  
    int c;
  
    while(1) {
      
        sem_wait(&fillCount);
        sem_wait(&buffMutex);
        c = *(buffer + bufPosition);
        Consume(c, pthread_self());
        --bufPosition;
        sem_post(&buffMutex);
        sem_post(&emptyCount);
        sleep(1);
    }
}


int main(void) {
  
    int i, error = 0;
    sem_init(&buffMutex, 0, 1);
    sem_init(&fillCount, 0, 0);

    printf("\nEnter number of Producers: ");
	  scanf("%d", &producersCount);
    producerThread = (pthread_t *)malloc(producersCount * sizeof(pthread_t));

    printf("\nEnter number of Consumers: ");
	  scanf("%d", &consumersCount);
	  consumerThread = (pthread_t *)malloc(consumersCount * sizeof(pthread_t));

    printf("\nEnter size of Buffer: ");
	  scanf("%d", &bufLength);
	  buffer = (int *)malloc(bufLength * sizeof(int));

	  sem_init(&emptyCount, 0, bufLength);

    // pthread_create() creates new thread
    for(i = 0; i < producersCount; ++i) {
      
      error = pthread_create(producerThread + i, NULL, &Producer, NULL);
      if(error != 0) {
          printf("\nProducer[%d] creation error: %s", i + 1, strerror(error));
      }
      
      else {
          printf("\nProducer[%d] created successfully.", i + 1);
      }
	  }

    for(i = 0; i < consumersCount; ++i) {
      
      error = pthread_create(consumerThread + i, NULL, &Consumer, NULL);
      
      if(error != 0) {
          printf("\nConsumer[%d] creation error: %s", i + 1, strerror(error));
      }
      
      else {
          printf("\nConsumer[%d] created successfully.", i + 1);
      }
    }

    printf("\n\n---------------------------------------\n");

    /* pthread_join() suspends execution of thread that has called it
       unless the target thread terminates */
    for(i = 0; i < producersCount; ++i) { pthread_join(*(producerThread + i), NULL); }
    
    for(i = 0; i < consumersCount; ++i) { pthread_join(*(consumerThread + i), NULL); }
    return 0;
}
