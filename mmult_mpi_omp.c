/** 
 * Incomplete program to multiply a matrix times a matrix using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>

#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1;	/* A x B computed using the omp-mpi code you write */
    double *cc2;	/* A x B computed using the conventional algorithm */
    int myid, numprocs;
    double starttime, endtime;
    MPI_Status status;

    /* insert other global variables here */
    int numsent = 0;
    int master = 0;
    int i,j;
    double ans;
    int sender = status.MPI_SOURCE;
    int anstype = status.MPI_TAG;
    int row = status.MPI_TAG;
    

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        FILE *mpi_Output;
        mpi_Output = fopen("clusterMPI.txt", "w");

        int max_matrix_size = atoi(argv[1]);
        for (int i = 1; i <= max_matrix_size; i++) {
            nrows = i;
            ncols = nrows;
	    aa = gen_matrix(nrows, ncols);
            bb = gen_matrix(ncols, nrows);
            cc1 = (double*)malloc(sizeof(double) * ncols); 
            if (myid == master) {
                // Master Code goes here
                starttime = MPI_Wtime();


                /* Insert your master code here to store the product into buffer */
                numsent = 0;
                MPI_Bcast(aa, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
                for (i = 0; i < min(numprocs-1, nrows); i++) {
                    for (j = 0; j < ncols; j++) {
                        cc1[j] = aa[i * ncols + j];
                    }  
                    MPI_Send(cc1, ncols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD);
                    numsent++;
                }
                for (i = 0; i < nrows; i++) {
                    MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, 
                        MPI_COMM_WORLD, &status);
                    sender = status.MPI_SOURCE;
                    anstype = status.MPI_TAG;
                    bb[anstype-1] = ans;
                    if (numsent < nrows) {
                        for (j = 0; j < ncols; j++) {
                            cc1[j] = aa[numsent*ncols + j];
                        }  
                        MPI_Send(cc1, ncols, MPI_DOUBLE, sender, numsent+1, 
                            MPI_COMM_WORLD);
                        numsent++;
                    } else {
                        MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                    }
                } 
                /* End of master code (that was copied from mxv_omp_mpi.c and altered) */

                endtime = MPI_Wtime();

                // Added for graphing
                char mpi_log_buffer[256];
                sprintf(mpi_log_buffer, "%d, %d, %f\n", nrows, nrows, endtime-starttime);
                fwrite(mpi_log_buffer, 1 , strlen(mpi_log_buffer) , mpi_Output);
		    
            } else {

                // Slave Code goes here
                MPI_Bcast(aa, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
                if (myid <= nrows) {
                    while(1) {
                        MPI_Recv(cc1, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, 
                            MPI_COMM_WORLD, &status);
                        if (status.MPI_TAG == 0){
                            break;
                        }
                        row = status.MPI_TAG;
                        ans = 0.0;
    #pragma omp parallel
    #pragma omp shared(ans) for reduction(+:ans)
                        for (j = 0; j < ncols; j++) {
                            ans += cc1[j] * aa[j];
                        }
                        MPI_Send(&ans, 1, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
                    }
                }
                /* End of slave code (that was copied from mxv_omp_mpi.c and altered) */

            }
        }
        fclose(mpi_Output);
    }
    else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
