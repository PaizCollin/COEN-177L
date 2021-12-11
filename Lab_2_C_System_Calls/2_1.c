// Collin Paiz
// 29 September 2021
// Lab2 - Programming in C and the use of system calls
// Description: This C program takes an integer argument which is the number of microseconds of delay for each process. The parent process creates a child process and each iterate through a for loop 100 times. This program is meant to visualize the delay and switching between parent and child processes. Using a delay of 5000 takes longer than a delay of 500, and the processes alternate at different points depending on how many are able to fit in the alloted time frame of the parent and child processes. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

// main function with command line arguments
int main(int argc, char *argv[]) {
	pid_t pid;
	int i, n = atoi(argv[1]);	// n microseconds to input from keyboard for delay
	printf("\n Before forking.\n");
	pid = fork();
	if(pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if(pid) {
		// parent process
		for(i = 0; i < 100; i++) {
			printf("\t \t \t Parent Process %d \n", i);
			usleep(n);
		}
	} else {
		// child process
		for(i = 0; i < 100; i++) {
			printf("Child Process %d\n", i);
			usleep(n);
		}
	}
	return 0;
}


