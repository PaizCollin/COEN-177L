// Collin Paiz
// November 10 2021
// Lab 8 - FIFO Page Replacement
// The following page replacement program replaces pages based on the
// FIFO method. The program keeps track of the place in the cache and
// adds pages to the cache as they arrive. If the page is already in
// the cache, then it continues, but if it isn't, then it is added to
// the next available spot in the cache. If there is no space left in
// the cache, the place in the cache loop back to the beginning, and
// the first page in is the first to be replaced. Each miss and each
// request is tracked, and then outputted to the terminal window, along
// with the calculated hit rate. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to 
    int pageno;
} ref_page;

int inCache(int page_num, ref_page cache[], int cacheSize) {
    int i;
    for(i = 0; i < cacheSize; i++) {
        if(cache[i].pageno == page_num) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file
    int iterCache = 0; // position in cache

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0; // keeps track of the total page requests
    
    for (i = 0; i < C_SIZE; i++){ // initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

        // if not found in cache
        // put page into cache, increment totalFaults, increment in cache
        if(inCache(page_num, cache, C_SIZE) == -1) {
            cache[iterCache].pageno = page_num;
            totalFaults++;
            iterCache = (iterCache + 1) % C_SIZE;
        }

        totalRequests++;
    }

    printf("%d - FIFO\n", C_SIZE);
    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", totalRequests);
    double numMisses = totalFaults;
    double numRequests = totalRequests;
    double missRate = (numMisses / numRequests);
    double hitRate = 1 - missRate;
    printf("Hit Rate = %f\n\n", hitRate);

    return 0;
}
