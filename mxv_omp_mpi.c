/** 
 * Program to multiply a matrix times a vector using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "mat.h"
#define min(x, y) ((x)<(y)?(x):(y))

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa, *b, *c;
    double *buffer, ans;
    double *times;
    double total_times;
    int run_index;
    int nruns;
    int myid, master, numprocs;
    double starttime, endtime;
    MPI_Status status;
    int i, j, numsent, sender;
    int anstype, row;
    FILE *fp;    

    srand(time(0));
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;

	// aa = (double*)malloc(sizeof(double) * nrows * ncols);
        b = (double*)malloc(sizeof(double) * ncols);
        c = (double*)malloc(sizeof(double) * nrows);
        buffer = (double*)malloc(sizeof(double) * ncols);
        master = 0;
        if (myid == master) {
            // Master Code goes here
            aa = gen_matrix(nrows, ncols);
            starttime = MPI_Wtime();
            numsent = 0;
            MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            for (i = 0; i < min(numprocs-1, nrows); i++) {
	            for (j = 0; j < ncols; j++) {
                    buffer[j] = aa[i * ncols + j];
                }  
                MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD);
                numsent++;
            }
            for (i = 0; i < nrows; i++) {
                MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, 
                    MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                anstype = status.MPI_TAG;
                c[anstype-1] = ans;
                if (numsent < nrows) {
                    for (j = 0; j < ncols; j++) {
                        buffer[j] = aa[numsent*ncols + j];
                    }  
                    MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1, 
                        MPI_COMM_WORLD);
                    numsent++;
                } else {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            } 
            endtime = MPI_Wtime();
            printf("%f\n",(endtime - starttime));

	    FILE *fp;
	    char buffer[16];
	    char *formatAddition = ", ";
            sprintf(buffer, "%d%s%f%s", ncols, formatAddition, endtime-starttime, formatAddition);

	    fp = fopen("FINAL_OUTPUT.txt", "a");
	    fwrite(buffer, 1 , strlen(buffer) , fp );

            fclose(fp);

        } else {
            // Slave Code goes here
            MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            if (myid <= nrows) {
	            while(1) {
	                MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, 
		                MPI_COMM_WORLD, &status);
	                if (status.MPI_TAG == 0){
	                    break;
                    }
	                row = status.MPI_TAG;
	                ans = 0.0;
#pragma omp parallel
#pragma omp shared(ans) for reduction(+:ans)
	                for (j = 0; j < ncols; j++) {
	                    ans += buffer[j] * b[j];
	                }
	                MPI_Send(&ans, 1, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
	            }
            }
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
