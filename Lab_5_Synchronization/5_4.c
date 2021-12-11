// Collin Paiz
// 20 October 2021
// Lab 5 - Task 4
// The following program is a solution to the common producer/consumer problem. 
// The main functions creates two threads, one being the producer, and the other
// being the consumer. Both the producer and consumer use a semaphore to enter 
// their respective critical sections. The producer's job is to generate a random
// value, place it into the buffer, print what was put into the buffer, and iterate.
// The consumer then prints out what the producer put in, and iterates. This cycle
// continues until the program is manually terminated using 'ctrl+c', which terminates
// the program as well as unlinks the semaphores. 

// Producer - Consumer with semaphores
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
sem_t *mutex, *full, *empty; 
int p, c, in, out; 

void *producer(void *arg) {
    int item;
    int p = (int)arg;
    srand(time(0));

    do {
        item = (rand() % 100);  // random number for producer
        sem_wait(empty);
        sem_wait(mutex);

        buff[in] = item;
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, 
in);
        in = (in+1) % BUFSIZE;
        sleep(5);
        
        sem_post(mutex);
        sem_post(full);

    } while (1);

    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;
    srand(time(0));

    do {
        sem_wait(full);
        sem_wait(mutex);
        
        item = buff[out];
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
        out = (out+1) % BUFSIZE;
        sleep(10);
        sem_post(mutex);
        sem_post(empty);

    } while (1);

    pthread_exit(0);
}

void cleanup(int sigtype){
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    printf("\n Terminating\n");
    
    exit(0);
}

int main () {
    signal(SIGINT,cleanup); 
    
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    full = sem_open("full", O_CREAT, 0644, 0);
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE);

    for (p = 0; p < NP; p++) {
        pthread_create (&tidP[p], NULL, producer, (void *)&tidP[p]);
    }

    for (c = 0; c < NC; c++) {
        pthread_create (&tidC[c], NULL, consumer, (void *)&tidC[c]);
    }

    // main thread waiting for consumer and producer threads to complete their tasks
    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }

    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");

    for(;;);
    return 0;
}
