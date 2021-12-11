// Collin Paiz
// November 10 2021
// Lab 8 - LRU Page Replacement
// The following page replacement program replaces pages based on the
// LRU method. Each page has its number and its age. The program first 
// checks to see if the page is already in the cache. If it is, then 
// the age of the page is set back to 0. If not, then the page is placed
// into the next available spot in the cache (if there is space), or it
// replaces the oldest page in the cache. Each iteration also increments
// the age of each page by 1. Each miss and each request is tracked, and 
// then outputted to the terminal window, along with the calculated hit rate. 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to 
    int pageno;
    int age;
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
    int oldest = -1;
    int j = -1;
    for(i = 0; i < cacheSize; i++) {
        if(cache[i].age == -1) {
            return i;
        } else if(cache[i].age > oldest) {
            j = i;
            oldest = cache[i].age;
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
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].age = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        int curPage = inCache(page_num, cache, C_SIZE);
        
        // increase age each turn
        for(i = 0; i < C_SIZE; i++) {
            if(cache[i].age != -1) {
                cache[i].age++;
            }
        }

        // if not found in cache
        // find its replacement, set age to 0, increment totalFaults
        // else, set the page's age to 0
        if(curPage == -1) {
            iterCache = findPlace(iterCache, cache, C_SIZE);
            cache[iterCache].pageno = page_num;
            cache[iterCache].age = 0;
            totalFaults++;
        } else {
            cache[curPage].age = 0;
        }

    	totalRequests++;
    }

    printf("%d - LRU\n", C_SIZE);
    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", totalRequests);
    double numMisses = totalFaults;
    double numRequests = totalRequests;
    double missRate = (numMisses / numRequests);
    double hitRate = 1 - missRate;
    printf("Hit Rate = %f\n\n", hitRate);

    return 0;
}
