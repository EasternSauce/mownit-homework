#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#define begin 0
#define end 1

double func1(double x, void *params) {
	return x*x;
}

double func2(double x, void *params) {
	return sqrt(x);
}

double func_def(double x, void *params) {
	return x;
}

int main(int argc, char *argv[]) {
	double eps = 10e-6;
	int op;
	if(argc > 1)
		op = atoi(argv[1]);
	size_t limit = 1000, npts = 2;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	double pts[] = {begin, end};
	switch(op) {
		case 1:
			F.function = &func1;
			break;
		case 2:
			F.function = &func2;
			break;
		default:
			F.function = &func_def;
			break;
	}
	F.params = &alpha;
	gsl_integration_qagp(&F, pts, npts, 0, eps, limit, w, &I, &abserr);

	printf("I(f) = %.20lf\tn = %zu\n", I, w->size);

	gsl_integration_workspace_free(w);
	return 0;
}
