#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

int a;

double func(double x, void *params) {
	return a;
}

int main(int argc, char *argv[]) {
	a = atoi(argv[1]);
	double begin = 0;
	double end = ((double)9/2) * M_PI;
	double eps = 1e-10;
	size_t limit = 1000;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_integration_qawo_table *wf = gsl_integration_qawo_table_alloc((double)a, (end - begin), GSL_INTEG_COSINE, 100);
	gsl_function F;
	double I, abserr, alpha;
	F.function = &func;
	F.params = &alpha;
	gsl_integration_qawo(&F, begin, 0, eps, limit, w, wf, &I, &abserr);

	//printf("I(f) = %.20lf\tn = %zu\n", I, w->size);
	printf("%d,a3,%d\n", a, w->size);
	
	gsl_integration_qawo_table_free(wf);
	gsl_integration_workspace_free(w);
	return 0;
}
