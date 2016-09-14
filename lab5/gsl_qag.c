#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#define begin 0
#define end 1

double root(double x, void * params){
	return sqrt(x);
}

double gsl_qag(double from, double to, size_t limit, double (*func)()){
	double eps = 10e-6;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	int key = 1;
	F.function = func;
	F.params = &alpha;
	gsl_integration_qag(&F, from, to, 0, eps, limit, key, w, &I, &abserr);

	gsl_integration_workspace_free(w);

	return I;

}

int main(int argc, char *argv[]) {
	printf("%f\n", gsl_qag(0.0, 1.0, (size_t)1000, root));
	return 0;
}
