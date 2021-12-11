/**************************
*	pipe()
**************************/

// Collin Paiz
// Lab 3 - Step 1
// 6 October 2021
// The parent function creates two children and closes both ends of the pipe. It then waits for its children to complete. The two children each close one end of the pipe, the upstream and downstream end, respectively. The first child, the producer, calls the producer function and writes to the pipe file and prints to the console what it put. Then the secnd child, the consumer, calls the consumer function and reads what the producer put and prints it to the console.  

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
#include <string.h>

// producer
void producer(FILE *pipe_write_end) {
	int i;
	for(i = 0; i < 10; i++) {
		fprintf(pipe_write_end, "%d ", i);
		printf("Producer: %d\n", i);
	}
	fclose(pipe_write_end);
	exit(0);
}

// consumer
void consumer(FILE *pipe_read_end) {
	int i;
	
	while(1) {
		int n = fscanf(pipe_read_end, "%d", &i);
		if(n == 1) {
			printf("Consumer: %d\n", i);
		} else {
			break;
		}
	}
	fclose(pipe_read_end);
	exit(0);
}

//main
int main(int argc, char *argv[]) {
 	int fds[2];
	FILE *pipe_write_end, *pipe_read_end;
	int i;
 	pipe(fds);
	
	pipe_read_end = fdopen(fds[0], "r");
	pipe_write_end = fdopen(fds[1], "w");

	/*child 1 producer */
	if (fork() == 0) {
		close(fds[0]);
		producer(pipe_write_end); 
	}
	/*child 2 consumer */
	else if (fork() == 0) {
		close(fds[1]);
		consumer(pipe_read_end); 
	}
	else {  /*parent closes both ends and wait for children*/
		fclose(pipe_read_end);
		fclose(pipe_write_end);
		wait(0);
		wait(0); 
	}
	return 0;
} 
