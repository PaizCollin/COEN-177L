// Collin Paiz
// 29 September 2021
// Lab2 - Programming in C and the use of system calls
// Description: This C program takes an integer argument which is the number of microseconds of delay. This program is similar to the first program (2_1.c), but it instead replaces processes with threads. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *parent(int i) {
	int j;
	for(j = 0; j < 100; j++) {
		printf("Parent Process %d\n", j);
		usleep(i);
	}
	pthread_exit(NULL);
}

void *child(int i) {
	int j;
	for(j = 0; j < 100; j++) {
		printf("\t \t \t Child Process %d\n", j);
		usleep(i);
	}
	pthread_exit(NULL);
}

// main function with command line arguments
int main(int argc, char *argv[]) {
	pid_t pid;
	pthread_t parentThread, childThread;
	int thr, n = atoi(argv[1]);	// n microseconds to input from keyboard for delay

	// parent thread
	thr = pthread_create(&parentThread, NULL, parent, n);
	
	// child thread
	thr = pthread_create(&childThread, NULL, child, n);
	
	pthread_exit(NULL);
	return 0;
}


