#ifndef MAT_H
#define MAT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


double *gen_matrix(int n, int m);
int compare_matrices(double* a, double* b, int nRows, int nCols);
double *read_matrix_from_file(const char *path);
void print_matrix(double *a, int nrows, int ncols);

int mmult(double *c, 
          double *a, int aRows, int aCols, 
          double *b, int bRows, int bCols);

int mmult_omp(double *c,
		      double *a, int aRows, int aCols,
		      double *b, int bRows, int bCols);

#endif
