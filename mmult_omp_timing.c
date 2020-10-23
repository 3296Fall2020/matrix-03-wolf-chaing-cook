/**
 * This file compares the time to multiply matrices
 * both unoptimized and with OMP. 
 */

#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>

#include "mat.h"

int main(int argc, char* argv[]) {
    struct timespec start;
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    int n;
    double times[2];

 clock_t t;

    if (argc > 1) {
        int max_matrix_size = atoi(argv[1]);
        FILE *unoptimized_Output, *openMP_Output;
        unoptimized_Output = fopen("clusterNoSIMD.txt", "w");
        openMP_Output = fopen("clusterOMP.txt", "w");


        for (int i = 1; i <= max_matrix_size; i++) {
            n = i;
            a = gen_matrix(n, n);
            b = gen_matrix(n, n);
            c1 = malloc(sizeof(double) * n * n);
            c2 = malloc(sizeof(double) * n * n);

            t = clock();  // Start time
            mmult(c1, a, n, n, b, n, n);
            t = clock() - t;  // End time
            double time_taken = ((double)t)/CLOCKS_PER_SEC;
            times[0] = time_taken;  // Time elapsed for non-omp multiplication
            
            
            t = clock();  // Start time
            mmult_omp(c2, a, n, n, b, n, n);
            t = clock() - t;  // End time
            time_taken = ((double)t)/CLOCKS_PER_SEC;
            times[1] = time_taken;  // Time elapsed for omp multiplication
            
            // Stuff we added to log timings for graphing
            char unoptimized_buffer[256];
            sprintf(unoptimized_buffer, "%d, %d, %f\n", i, n, times[0]);
            fwrite(unoptimized_buffer, 1 , strlen(unoptimized_buffer) , unoptimized_Output);

            char omp_buffer[256];
            sprintf(omp_buffer, "%d, %d, %f\n", i, n, times[1]);
            fwrite(omp_buffer, 1 , strlen(omp_buffer) , openMP_Output);

            // compare_matrices(c1, c2, n, n);
        }

        fclose(unoptimized_Output);
        fclose(openMP_Output);
    } else {
        fprintf(stderr, "Usage %s <n>\n", argv[0]);
    }





















/*   if (argc > 1) {
        n = atoi(argv[1]);
        a = gen_matrix(n, n);
        b = gen_matrix(n, n);
        c1 = malloc(sizeof(double) * n * n);
        c2 = malloc(sizeof(double) * n * n);
        clock_gettime(CLOCK_REALTIME, &start);
        mmult(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[0] = deltaTime(&start, &end);
        printf("%d %f", n, times[0]);
        clock_gettime(CLOCK_REALTIME, &start);
        mmult_omp(c2, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[1] = deltaTime(&start, &end);
        printf(" %f", times[1]);
        printf("\n");
        compare_matrices(c1, c2, n, n);
    } else {
        fprintf(stderr, "Usage %s <n>\n", argv[0 }
*/
}

