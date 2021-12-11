// Collin Paiz
// Lab 9 - Step 3
// 17 November 2021
// This program performs a similar task to step 2, but it also takes an input for the buffer size: 100, 1000,10000 and 1000000.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[2]) {
    int buff = atoi(argv[2]);
    char buffer[buff];
    FILE *fp;
    fp = fopen(argv[1], "rb");

    while (fread(buffer, sizeof(buffer), 1, fp)){

    }

    fclose(fp);
    return 0;
}
