// Collin Paiz
// Lab 9 - Step 5
// 17 November 2021
// This program performs a similar task to step 4, but it implements threads to write to the file. It takes
// the inputs of a filename, a buffer size, and a thread count. This program is then used to measure the I/O
// performance by timing how long it takes to read and write.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int BUFFSIZE;
int NTHREADS;

typedef struct {
    char *filename;
}NAME;

void *go(void *arg) { 
    NAME *name = (NAME *)arg;
    char *originalFile = (*name).filename;
    char buffer[BUFFSIZE];
    char filename[20];
    sprintf(filename, "%scopy%d.txt", originalFile, BUFFSIZE);
    FILE *fp, *fp2;
    fp = fopen(originalFile, "rb");
    fp2 = fopen(filename, "wb");
    while (fread(buffer, sizeof(buffer), 1, fp)){
        fwrite(buffer, sizeof(buffer), 1, fp2);
    }

    fclose(fp);
    fclose(fp2);
}

int main(int argc, char *argv[])  {
    BUFFSIZE = atoi(argv[2]);
    NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];

    int i;
    for(i = 0; i < NTHREADS; i++) {
	NAME *name;
	name = malloc(sizeof(NAME));
	(*name).filename = argv[1];
	pthread_create(&threads[i], NULL, go, (void *)name);
    }

    for(i = 0; i < NTHREADS; i++) {
	pthread_join(threads[i], NULL);
    }	    
}
