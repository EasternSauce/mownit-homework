#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <time.h>
#include <sys/time.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

const int MEASURES = 30;
static struct timeval start, end;
const int MAX = 10000;
const int MAX_LU = 1100;
const int MAX_TRIDIAG = 1100;

gsl_vector * createRandomVector(int vsize){
	gsl_vector * v = gsl_vector_alloc (vsize);
	for (int i = 0; i < vsize; i++){
		gsl_vector_set (v, i, rand()%MAX+1);
	}
	return v;
}

gsl_matrix * createRandomMatrix(int msize){
	gsl_matrix * m = gsl_matrix_alloc(msize, msize);
	for (int i = 0; i < msize; i++){
		for (int j = 0; j < msize; j++){
			gsl_matrix_set(m, i, j, rand()%MAX+1);
		}
	}
	return m;
}

gsl_matrix * createRandomTridiagonalMatrix(int msize){
	gsl_matrix * m = gsl_matrix_alloc(msize, msize);
	for (int i = 0; i < msize; i++){
		for (int j = 0; j < msize; j++){
			if(abs(i-j) <= 1) gsl_matrix_set(m, i, j, rand()%MAX+1);
			else gsl_matrix_set(m, i, j, 0);
		}
	}
	return m;

}

void printVector(gsl_vector * v, int size){
	for (int i = 0; i < size; i++){
		printf ("(%d) = %g ",  i, 
				gsl_vector_get (v, i));
	}
	printf("\n");
}

void printMatrix(gsl_matrix * m, int size){
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf ("(%d, %d) = %g ",  i, j,
					gsl_matrix_get (m, i, j));
		}
		printf("\n");
	}
}


gsl_vector * computeLU(gsl_matrix * mo, gsl_vector * bo, int size){
	gsl_matrix * m = gsl_matrix_alloc(size, size);
	gsl_matrix_memcpy(m, mo);
	gsl_vector * b = gsl_vector_alloc(size);
	gsl_vector_memcpy(b, bo);
	gsl_vector * x = gsl_vector_alloc(size);

	int s;

	gsl_permutation * p = gsl_permutation_alloc (size);

	gsl_linalg_LU_decomp (m, p, &s);

	gsl_linalg_LU_solve (m, p, b, x);

	gsl_matrix_free(m);
	gsl_vector_free(b);

	return x;

}

gsl_vector * getSuperdiagonal(gsl_matrix * m, int size){
	gsl_vector * v = gsl_vector_alloc(size-1);
	for (int i = 0; i < size-1; i++){
		gsl_vector_set(v, i, (gsl_matrix_get (m, i, i+1)));
	}
	return v;
}

gsl_vector * getDiagonal(gsl_matrix * m, int size){
	gsl_vector * v = gsl_vector_alloc(size);
	for (int i = 0; i < size; i++){
		gsl_vector_set(v, i, (gsl_matrix_get (m, i, i)));
	}
	return v;
}

gsl_vector * getSubdiagonal(gsl_matrix * m, int size){
	gsl_vector * v = gsl_vector_alloc(size-1);
	for (int i = 0; i < size-1; i++){
		gsl_vector_set(v, i, (gsl_matrix_get (m, i+1, i)));
	}
	return v;

}

gsl_vector * computeTridiag(gsl_vector * sup, gsl_vector * diag, gsl_vector * sub, gsl_vector * bo, int size){
	gsl_vector * b = gsl_vector_alloc(size);
	gsl_vector_memcpy(b, bo);
	gsl_vector * x = gsl_vector_alloc(size);

	gsl_linalg_solve_tridiag(diag, sup, sub, b, x);

	gsl_vector_free(b);
	return x;
}



void test_tri(){
	/*
	int size = 3;
	gsl_matrix * m = createRandomTridiagonalMatrix(size); 
	printMatrix(m, size);
	gsl_vector * b = createRandomVector(size);
	printf("\n");
	printVector(b, size);
	printf("\n");
	printVector(computeLU(m, b, size), size);

	printf("\n");

	gsl_vector * sup = getSuperdiagonal(m, size);
	gsl_vector * diag = getDiagonal(m, size);
	gsl_vector * sub = getSubdiagonal(m, size);
	printVector(computeTridiag(sup, diag, sub, b, size), size);
	gsl_vector_free(sup);
	gsl_vector_free(diag);
	gsl_vector_free(sub);
	*/

	FILE * f = fopen("lu.txt", "w");

	fprintf(f, "time,size\n");
	for(int i = 0; i < MEASURES; i++){
		int size = (MAX_LU*(i+1)/MEASURES);
		gsl_matrix * m = createRandomTridiagonalMatrix(size); 
		gsl_vector * b = createRandomVector(size);

		gettimeofday(&start, NULL);

		computeLU(m, b, size);

		gettimeofday(&end, NULL);

		fprintf(f, "%ld,%d\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec, size);

		gsl_matrix_free (m);
		gsl_vector_free (b);

	}

	f = fopen("tridiag.txt", "w");

	fprintf(f, "time,size\n");
	for(int i = 0; i < MEASURES; i++){
		int size = (MAX_TRIDIAG*(i+1)/MEASURES);
		gsl_matrix * m = createRandomTridiagonalMatrix(size); 
		gsl_vector * b = createRandomVector(size);

		gsl_vector * sup = getSuperdiagonal(m, size);
		gsl_vector * diag = getDiagonal(m, size);
		gsl_vector * sub = getSubdiagonal(m, size);

		gettimeofday(&start, NULL);

		computeTridiag(sup, diag, sub, b, size);

		gettimeofday(&end, NULL);

		fprintf(f, "%ld,%d\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec, size);

		gsl_matrix_free (m);
		gsl_vector_free (b);
		gsl_vector_free(sup);
		gsl_vector_free(diag);
		gsl_vector_free(sub);

	}


	fclose(f);

}


int main(){
	srand(time(NULL));
	test_tri();


	return 0;
}

