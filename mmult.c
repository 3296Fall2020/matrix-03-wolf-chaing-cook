/**
 * An unoptimized implementation of matrix multiplication.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "mat.h"

/**
 * An unoptimized algorithm for matrix multiplication.
 * 
 * @param c : the matrix in which to place the result of the matrix multiplication.
 * @param a : the first matrix.
 * @param aRows : the number of rows in a.
 * @param aCols : the number of columns in a.
 * @param b : the second matrix.
 * @param bRows : the number of rows in b.
 * @param bCols : the number of columns in b.
 * @return 0 if the matrix multiplication is successful.
 */

void print_Matrix(double *a, int rows, int cols);

int mmult(double *c, 
	  double *a, int aRows, int aCols, 
	  double *b, int bRows, int bCols) 
{

    for(int i = 0; i < aRows; ++i) 
    {
      for(int j = 0; j < bCols; ++j) 
      {
        c[i * bCols + j] = 0;
      }
      for(int k = 0; k < aRows; ++k) 
      {
        for (int j = 0; j < bCols; j++)
        {
          c[i * bCols + j] += a[i * aRows + k] * b[k * bCols + j];
        }
      }
    }

  return 0;
}//end mmult()

double* gen_matrix(int n, int m)
{
  double* a = malloc(sizeof(double) * n * m);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      a[i*m + j] = (double)rand()/RAND_MAX;
    }
  }
  return a;
}//end gen_matrix()


void compare_matrices(double* a, double* b, int nRows, int nCols)
{
  int n = nRows * nCols;
  for (int k = 0; k < n; ++k)
  {
    if (fabs(a[k]-b[k])/fabs(a[k]) > 1e-12)
    {
      int i = k/nCols;
      int j = k%nCols;
      printf("a[%d][%d] == %.12g\nb[%d][%d] == %.12g\ndelta == %.12g\nrelerr == %.12g\n",
              i, j, a[k], i, j, b[k], fabs(a[k]-b[k]), fabs(a[k]-b[k])/fabs(a[k]));
      return;
    }
  }
  printf("Matrices are the same\n");
}//end compare_matrices()


void print_Matrix(double* a, int rows, int cols)
{
  printf("\n");
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      printf("%lf ", a[i*rows + j]);
    }
    printf("\n");
  }
}//end print_Matrix()



