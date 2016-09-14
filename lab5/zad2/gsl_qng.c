#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

int a;

double func(double x, void *params) {
	return (a * cos(a*x));
}

int main(int argc, char *argv[]) {
	a = atoi(argv[1]);
	double begin = 0;
	double end = ((double)9/2) * M_PI;
	double eps = 1e-2;
	gsl_function F;
	double I, abserr, alpha;
	size_t neval;
	F.function = &func;
	F.params = &alpha;
	gsl_integration_qng(&F, begin, end, 1e-1, eps, &I, &abserr, &neval);

	//printf("I(f) = %.20lf\tn = %zu\n", I, neval);
	printf("%d,a1,%d\n", a, neval);

	return 0;
}
