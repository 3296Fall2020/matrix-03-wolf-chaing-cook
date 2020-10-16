//Matrix Multiplication for MPI

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define min(x,y) ((x)<(y)?(x):(y))

int main(int argc, char* argv[]){

	int nrows, ncols;
	double *aa, *b, *c;
	double *buffer, ans;
	double *times;
	double total_times;
	int run_index;
	int nruns;
	int myid, numprocs;
	double starttime, endtime;
	MPI_Status status;
	int i, j, numsent, sender;
	int anstype, row;
	srand(time(0));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if(argc > 1){
		nrows = atoi(argv[1]);
		ncols = nrows;
		aa = (double*)malloc(sizeof(double)* nrows * ncols);
		b = (double*)malloc(sizeof(double) * ncols);
		c = (double*)malloc(sizeof(double) * nrows);
		buffer = (double*)malloc(sizeof(double) * ncols);

	if(myid == 0){
	
	//for the controller process
	for(i = 0; i < nrows; i++){
	for(j= 0; j < ncols; j++){
	aa[i*ncols + j] = (double)rand()/RAND_MAX;
		}//end of for
	}//end of for
	
	starttime = MPI_Wtime();
	numsent = 0;
	MPI_Bcast(b, ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for(i = 0; i < min(numprocs-1, nrows); i++){
		for(j = 0; j < ncols; j++){
			buffer[j] =aa[i * ncols + j];
	}//end of for
	MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD);
	numsent++;
	}//end of for

	for(i = 0; i < nrows; i++){
		MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
		MPI_COMM_WORLD, &status);
	sender = status.MPI_SOURCE;
	anstype = staus.MPI_TAG;
	c[anstype-1] = ans;
	
	if(numsent < nrows){
		for(j = 0; j < ncols; j++){
	buffer[j] = aa[numsent*ncols+j];
		}//end of for

	MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1, MPI_COMM_WORLD);
	numsent++;

	}//end of if

	else{
	MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
	}//end of sle
	endtime = MPI_Wtime();
	printf("%f\n", (endtime - starttime));

	}

	else{
	//for the worker
	MPI_Bcast(b, ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if(myid <= nrows){
		while(1){
			MPI_Recv(buffer, nCols, MPI_DOUBLE, 0, MPI_ANY_TAG,
			MPI_COMM_WORLD, &status);

	if(status.MPI_TAG == 0){
	break;
	}//end of if

	#pragma omp shared(ans) for reduction(+:ans)
	ans += buffer[j] * b[j];
	}//end of while
	}//end of if
	}//end of else

	}//end of if
	}//end of if
}//main
