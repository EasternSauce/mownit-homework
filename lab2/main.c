#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <time.h>
#include <sys/time.h>

const int MEASURES = 30;
const int BIAS1_MAX = 10000000;
const int BIAS2_MAX = 10000;
const int BIAS3_MAX = 1000;
static struct timeval start, end;

gsl_vector * createRandomVector(int vsize){
	gsl_vector * v = gsl_vector_alloc (vsize);
	for (int i = 0; i < vsize; i++){
		gsl_vector_set (v, i, rand()%10000);
	}
	return v;
}

gsl_matrix * createRandomMatrix(int msize){
	gsl_matrix * m = gsl_matrix_alloc(msize, msize);
	for (int i = 0; i < msize; i++){
		for (int j = 0; j < msize; j++){
			gsl_matrix_set(m, i, j, rand()%10000);
		}
	}
	return m;
}

void test_blas1(){
	FILE * f = fopen("blas1.txt", "w");

	fprintf(f, "time,vsize\n");
	for(int i = 0; i < MEASURES; i++){
		int vsize = (BIAS1_MAX*(i+1)/MEASURES);
		gsl_vector * v1 = createRandomVector(vsize); 
		gsl_vector * v2 = createRandomVector(vsize); 
		double r;

		gettimeofday(&start, NULL);

		gsl_blas_ddot(v1, v2, &r);

		gettimeofday(&end, NULL);

		fprintf(f, "%ld,%d\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec, vsize);

		gsl_vector_free (v1);
		gsl_vector_free (v2);

	}

	fclose(f);

}

void test_blas2(){
	FILE * f = fopen("blas2.txt", "w");

	fprintf(f, "time,vsize\n");

	for(int i = 0; i < MEASURES; i++){
		int vsize = (BIAS2_MAX*(i+1)/MEASURES) + 1;

		gsl_vector * v1 = createRandomVector(vsize); 
		gsl_vector * v2 = createRandomVector(vsize); 
		gsl_matrix * m1 = createRandomMatrix(vsize);

		gettimeofday(&start, NULL);

		gsl_blas_dgemv (CblasNoTrans, rand()%10000, m1, v1, rand()%10000, v2);

		gettimeofday(&end, NULL);

		fprintf(f, "%ld,%d\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec, vsize);

		gsl_vector_free (v1);
		gsl_vector_free (v2);
		gsl_matrix_free (m1);
	}

	fclose(f);
}

void test_blas3(){
	FILE * f = fopen("blas3.txt", "w");

	fprintf(f, "time,vsize\n");

	for(int i = 0; i < MEASURES; i++){
		int vsize = (BIAS3_MAX*(i+1)/MEASURES) + 1;
		gsl_matrix * m1 = createRandomMatrix(vsize);
		gsl_matrix * m2 = createRandomMatrix(vsize);
		gsl_matrix * m3 = createRandomMatrix(vsize);

		gettimeofday(&start, NULL);

		gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, rand()%10000, m1, m2, rand()%10000, m3);

		gettimeofday(&end, NULL);

		fprintf(f, "%ld,%d\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec, vsize);

		gsl_matrix_free (m1);
		gsl_matrix_free (m2);
		gsl_matrix_free (m3);
	}

	fclose(f);
}


int main()
{
	srand(time(NULL));

	test_blas1();
	test_blas2();
	test_blas3();


	return 0;
}

