// Collin Paiz
// November 10 2021
// Lab 8 - Second Change Page Replacement
// The following page replacement program replaces pages based on the
// second-chance method. Each page has a page number and a bit to keep
// track of its "second-chance". If the page is not found, then the program
// searches for an available spot in the cache. If there isn't an opening,
// then it returns the spot of the last page in the cache that doesn't have
// a second chance (bit = 0). Every page's bit is then set back to 0 after
// the replacement. If the page is already in the cache, then it's bit is
// set to 1 and given its "second chance", as this indicates it may be used
// frequently. Each miss and each request is tracked, and then outputted to 
// the terminal window, along with the calculated hit rate. 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to 
    int pageno;
    int bit;
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

int findPlace(int iterCache, ref_page cache[], int cacheSize) {
    int i;
    int j = 0;

    for(i = 0; i < cacheSize; i++) {
        if(cache[i].bit == -1) {    // available spot
            return i;
        }
    }

    for(i = 0; i < cacheSize; i++) {
        if(cache[i].bit == 1) {     // set bit back to 0
            cache[i].bit--;
        } else if(cache[i].bit == 0) {      // no second chance
            j = i;
        }
    }

    return j;
}

int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file
    int iterCache = 0; // position in cache

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0; // keeps track of the total page requests
    
    for (i = 0; i < C_SIZE; i++){ //initialise cache array  
         cache[i].pageno = -1;
         cache[i].bit = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        int curPage = inCache(page_num, cache, C_SIZE);

    	// if not found in cache
        // put page into cache, increment totalFaults, increment in cache
        if(curPage == -1) {
            iterCache = findPlace(iterCache, cache, C_SIZE);
            cache[iterCache].pageno = page_num;
            cache[iterCache].bit = 0;
            totalFaults++;
        } else {
            cache[iterCache].bit = 1;
        }

        totalRequests++;
    }

    printf("%d - Second Chance\n", C_SIZE);
    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", totalRequests);
    double numMisses = totalFaults;
    double numRequests = totalRequests;
    double missRate = (numMisses / numRequests);
    double hitRate = 1 - missRate;
    printf("Hit Rate = %f\n\n", hitRate);

    return 0;
}
