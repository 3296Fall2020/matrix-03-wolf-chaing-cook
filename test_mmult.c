#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "mat.h"
#include "mmult.h"

#define MAT_SIZE 5

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual) {
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    mmult(c_calc, a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE);

    int are_same = compare_matrices(c_actual, c_calc, MAT_SIZE, MAT_SIZE);

    free(c_calc);

    return are_same;
}


int main(int argc, char* argv[]) 
{
    int max_matrix_size = atoi(argv[1]);
    clock_t t;
    double *a, *b, *c_calc;

    FILE *vectorized_Output;
    vectorized_Output = fopen("clusterVecSIMD.txt", "w");

    for (int i = 1; i <= max_matrix_size; i++) 
    {
        double *a = gen_matrix(i, i);;
        double *b = gen_matrix(i, i);;
        double *c_calc = malloc(sizeof(double) * i * i);
        
        t = clock();  // Start time
        mmult_v(c_calc,a, i, i, b, i, i);
        t = clock() - t;  // End time
        double time_taken = ((double)t)/CLOCKS_PER_SEC;

        
        // Stuff we added to log timings for graphing
        char vectorized_buffer[256];
        sprintf(vectorized_buffer, "%d, %d, %f\n", i, i, time_taken);
        fwrite(vectorized_buffer, 1 , strlen(vectorized_buffer) , vectorized_Output);
        // printf("%f\n", time_taken);        
    }//end for()

    fclose(vectorized_Output);
}//end main()


















/*
int main(void) 
{
    double *a = read_matrix_from_file("a.txt");
    double *b = read_matrix_from_file("b.txt");
    double *c_actual = read_matrix_from_file("c.txt");
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    if(!test_unoptimized(a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE, c_actual)) {
        exit(1);
    }

    puts("All tests pass.");

    free(a);
    free(b);
    free(c_actual);
}*/
