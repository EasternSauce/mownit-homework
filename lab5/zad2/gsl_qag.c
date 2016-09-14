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
	double eps = 1e-10;
	size_t limit = 1000;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	int key = 1;
	F.function = &func;
	F.params = &alpha;
	gsl_integration_qag(&F, begin, end, 1e-1, eps, limit, key, w, &I, &abserr);

	//printf("I(f) = %.20lf\tn = %zu\n", I, w->size);
	printf("%d,a2,%d\n", a, w->size);

	gsl_integration_workspace_free(w);
	return 0;
}
