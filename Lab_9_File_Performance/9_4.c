// Collin Paiz
// Lab 9 - Step 4
// 17 November 2021
// This program makes copies of each of the files from step 1 by writing its contents to another file.
// It is then used to measure IO performance by timing how long it takes to perform its tasks.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[2])  {
    int buff = atoi(argv[2]);
    char buffer[buff];

    char filename[20];
    sprintf(filename, "%scopy%d.txt", argv[1], buff);
    FILE *fp, *fp2;
    fp = fopen(argv[1], "rb");
    fp2 = fopen(filename, "wb");

    while (fread(buffer, sizeof(buffer), 1, fp)){
        fwrite(buffer, sizeof(buffer), 1, fp2);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}
