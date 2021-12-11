/**************************
*   Lab3 - pipe()
**************************/

// Collin Paiz
// Lab 3 - Step 3
// 6 October 2021
// Modifies 3_2.c. The writer passes the ls command to the upstream end of the pipe and the downstream then prints it out in the same spaced-out formatting as 3_2.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
  
	// creates a child; upstream
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
    	dup2(fds[1], 1);
	close(fds[0]);
	execlp("ls", "ls", 0);
       for(i=0;i<argc;i++){
           write(fds[1],argv[i],strlen(argv[i]));
       }
       exit(0);
   }
	//creates a child; downstream
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }

       exit(0);
    }
	// parent waits
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
