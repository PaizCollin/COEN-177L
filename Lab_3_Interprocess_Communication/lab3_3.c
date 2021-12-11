/**************************
*	pipe()
**************************/

// Collin Paiz
// Lab 3 - Step 4
// 6 October 2021
// The parent function creates two children and closes both ends of the pipe. It then waits for its children to complete. The two children each close one end of the pipe, the upstream and downstream end, respectively. The first child duplicates to the downstream and executes "grep" "root", and the second child duplicates to the upstream and executes "cat" with argument "/etc/passwd", resulting in the output "cat /etc/passwd | grep root". 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h>
 
//main
int main(int argc, char *argv[]) {
 	int fds[2];
 	pipe(fds);
	
	/*child 1 grep root */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", (char *)0); 
		exit(0);
	}
	/*child 2 cat /etc/passwd */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", (char *)0);
		exit(0);
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
	return 0;
} 
