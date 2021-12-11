/**************************
*	pipe()
**************************/

// Collin Paiz
// Lab 3 - Step 1
// 6 October 2021
// The parent function creates two children and closes both ends of the pipe. It then waits for its children to complete. The two children each close one end of the pipe, the upstream and downstream end, respectively. The first child duplicates to the downstream and executes "sort", and the second child duplicates to the upstream and executes "ls", resulting in the output of "ls | sort". 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("sort", "sort", 0); 
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("ls", "ls", 0); 
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
} 
