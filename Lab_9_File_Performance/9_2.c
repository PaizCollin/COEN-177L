// Collin Paiz
// Lab 9 - Step 2
// 17 November 2021
// This program reads each file that was created in step 1. It is then used to measure IO performance by
// timing how long it takes to read.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");

    while (fread(buffer, sizeof(buffer), 1, fp)){

    }

    fclose(fp);
    return 0;
}
