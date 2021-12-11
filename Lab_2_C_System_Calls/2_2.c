// Collin Paiz
// 29 September 2021
// Lab2 - Programming in C and the use of system calls
// Description: This C program takes an integer argument which is the number of microseconds of delay for each process. This program creates 6 child processes which results in a total of 7 processes. The parent process creates two child processes, and then those two children create two children of their own, for a total of 7 processes, with each parent creating either 0 or 2 processes. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

// main function with command line arguments
int main(int argc, char *argv[]) {
	pid_t pid1, pid2, pid3, pid4;
	int n = atoi(argv[1]);			// n microseconds of delay based on keyboard input
	printf("\n Before forking.\n");
	pid1 = fork();
	if(pid1 == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}

	if(pid1) {
		pid2 = fork();			// create child process 1_1
		if(pid2 == -1) {
			fprintf(stderr, "can't fork, error %d\n", errno);
		}
		if(pid2) {
			printf("Parent with %d pid\n", getpid());
			usleep(n); 	
		} else {
			pid3 = fork();		// create child process 2_1
			if(pid3 == -1) {
				fprintf(stderr, "can't fork, error %d\n", errno);
			}
			if(pid3) {
				pid4 = fork();	// create child process 3_1
				if(pid4 == -1) {
					fprintf(stderr, "can't fork, error %d\n", errno);
				}
				if(pid4) {
					printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
					usleep(n);
				} else {
					printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
					usleep(n);
				}
			} else {
				printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
				usleep(n);
			}
		}
	} else {
		pid2 = fork();			// create child process 1_2
		if(pid2 == -1) {
			fprintf(stderr, "can't fork, error %d\n", errno);
		} 
		if(pid2) {
			pid3 = fork();		// create child process 2_2
			if(pid3 == -1) {
				fprintf(stderr, "can't fork, error %d\n", errno);
			}
			if(pid3) {
				printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
				usleep(n);
			} else {
				printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
				usleep(n);
			}		
		} else {
			printf("Child with %d pid, Parent with %d pid\n", getpid(), getppid());
			usleep(n);
		}
	}
	
	return 0;
}


