// Collin Paiz
// Lab 4 - Step 3: Matrix Multiplication with Threads
// 13 October 2021
// The objective of this lab was to create a program that calculates the dot product of two matrices. The program starts by initializing two matrices of size NxM and MxL with random values. It then creates N threads and feeds in the value i for each row i in the final matrixC. Each thread multiplies the corresponding values in matrixA and matrixB using a nested for loop, and those values are summed up to find the value to be put into matrixC. The main thread waits for the child threads to complete and then the matrices are printed out. 

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// values of N, M, L
#define N 2
#define M 3
#define L 2

pthread_t threads[N];

// matrices A, B, C
double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

// function prototypes
void initializeMatrix(int r, int c, double matrix[r][c]);
void *multiplyRow(void* arg);
void printMatrix(int r, int c, double matrix[r][c]);

int main() {
	int i;

	// assign random values for matrixA, matrixB
	initializeMatrix(N, M, matrixA);
	sleep(2);
	initializeMatrix(M, L, matrixB);

	// create N threads
	for (i = 0; i < N; i++) {
		pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);
	}

	// main thread waits for child threads to complete
	for (i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}
	
	// print Matrix A, B, C
	printMatrix(N, M, matrixA);
	printMatrix(M, L, matrixB);
	printMatrix(N, L, matrixC);

	return 0;
}

void initializeMatrix(int r, int c, double matrix[r][c]) {
	srand(time(NULL));
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			matrix[i][j] = rand() / 100000000;
		}
	}
}

void *multiplyRow(void* arg) {
	int j, k;
	int i = (int)(size_t *)arg;

	// printf("%d\n", i);
	for(j = 0; j < L; j++) {
		double temp = 0;
		for(k = 0; k < M; k++) {
			temp += matrixA[i][k] * matrixB[k][j];
		}
		matrixC[i][j] = temp;
	}
}

void printMatrix(int r, int c, double matrix[r][c]) {
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

