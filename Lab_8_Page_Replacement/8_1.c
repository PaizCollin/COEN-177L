// Collin Paiz
// November 10 2021
// Lab 8 - Task 1
// The following program opens a file called 'testInput.txt' in write mode. Then
// it enters a for-loop and formats the buffer value from a random integer and puts
// it into the file. Then the file closes and the program terminates.

#include <stdio.h>
#include <stdlib.h>

#define someNumber 10000
#define capNumber 100

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<someNumber; i++){
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}