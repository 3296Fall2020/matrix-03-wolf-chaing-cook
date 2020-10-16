#include <stdio.h>
#include "mat.h"

int main(int argc, char* argv)
{
		double *a, *b, *MMULT, *SIMD;
		FILE *datatable = fopen("datatable.txt", "w");

		for (int i = 100; i < 500; i += 100)
		{
				a = gen_matrix(i, i);
				b = gen_matrix(i, i);

				MMULT = gen_matrix(i, i);
				SIMD = gen_matrix(i, i);

				fprintf(datatable, "%d, ", i);
				double mmultTime = mmult(MMULT, a, i, i, b, i, i);

				fprintf(datatable, "%f, ", mmultTime);

				double simdTime = mmult_SIMD(SIMD, a, i, i, b, i, i);

				fprintf(datatable, "%f, ", simdTime);
				fprintf(datatable, "\n");
		}

		fclose(datatable);
		return 0;
}
