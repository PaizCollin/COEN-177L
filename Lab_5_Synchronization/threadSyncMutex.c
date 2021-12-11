// Collin Paiz
// 20 October 2021
// Lab 5 - Task 3
// The following program is an edited version of threadSync.c. This program
// replaces semaphores with mutex locks. The main function creates threads 
// and waits for them to compelete. Each thread waits to obtain the lock
// before entering thei respective critical sections. Upon completion of
// their critical sections, the lock is unlocked, and the next thread may
// obtain the lock. 

// Thread Sychronization
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
//sem_t *mutex; 
pthread_mutex_t m;

void* go(void* arg) { 
  pthread_mutex_lock(&m); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
  sleep(1); 
  pthread_mutex_unlock(&m); //exit section 
  pthread_exit(0);
} 

int main() { 
pthread_mutex_init(&m, NULL);
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
pthread_mutex_destroy(&m); 
return 0; 
} 
