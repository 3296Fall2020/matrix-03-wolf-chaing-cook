#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>

#include "mat.h"

void printMatrix();

int main(int argc, char* argv[]){

	struct timespec start;
	struct timespec end;
	struct timespec res;
	double *a, *b, *c1, *c2;
	int n;
	double times[2];
	
	
	if(argc > 1){
	
		n = atoi(argv[1]);
		a = gen_matrix(n, n);
		b = gen_matrix(n, n);
		c1 = malloc(sizeof(double) * n * n);
		c2 = malloc(sizeof(double) * n * n);
		clock_gettime(CLOCK_REALTIME, &start);
		mmult(cl, a, n, n, b, n, n);
		clock_gettime(CLOCK_REALTIME, &end);
		times[0] = deltaTime(&start, &end);
		printf("%d %f", n, times[0]);
		clock_gettime(CLOCK_REALTIME, &start);
		mmult_omp(c2, a, n, n, b, n, n);
		clockgettime(CLOCK_REALTIME, &end);
		times[1] = deltaTime(&start, &end);
		printf(" %f", times[1]);
		printf("\n");
		compare_matricies(c1, c2, n, n);

	}//end of if

	else{
	fprintf(stderr, "Usage %s <n>\n", argv[0]);
	}//end of else
}//end of main


void printMatrix(){
	
}//end of printMatrix
