#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double func(double x, void *params) {
	return 1/(pow(x,2) + 4);
}

int main(int argc, char *argv[]) {
	double begin = 0;
	double eps = 1e-10;
	size_t limit = 1000;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	F.function = &func;
	F.params = &alpha;
	gsl_integration_qagiu(&F, begin, 0, eps, limit, w, &I, &abserr);

	printf("I(f) = %.20lf\tn = %zu\n", I, w->size);

	gsl_integration_workspace_free(w);
	return 0;
}
