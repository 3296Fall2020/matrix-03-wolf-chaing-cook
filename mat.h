#ifndef MAT_H
#define MAT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>

double *gen_matrix(int n, int m);
int compare_matrices(double* a, double* b, int nRows, int nCols);
double *read_matrix_from_file(const char *path);
void print_matrix(double *a, int nrows, int ncols);

double mmult(double *c, 
          double *a, int aRows, int aCols, 
          double *b, int bRows, int bCols);

int mmult_omp(double *c,
		      double *a, int aRows, int aCols,
		      double *b, int bRows, int bCols);

double mmult_SIMD(double *c,
				  double *a, int aRows, int aCols,
				  double *b, int bRows, int bCols);

double deltaTime(struct timespec *start, struct timespec *end);
#endif
