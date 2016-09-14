#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

int count = 0;

double root(double x, void * params){
	count++;
	return sqrt(x);
}

int get_count(){
	int r = count;
	count = 0;
	return r;
}

double int_rect(double from, double to, double (*func)()){
	double n = 1000;
	double h = (to-from)/n;
	double sum = 0.0, x;
	for(x=from; x <= (to-h); x += h)
		sum += func(x);
	return h*sum;
}

double gsl_qng(double from, double to, double (*func)()){
	double eps = 10e-6;
	gsl_function F;
	double I, abserr, alpha;
	size_t neval;
	F.function = func;
	F.params = &alpha;
	gsl_integration_qng(&F, from, to, 0, eps, &I, &abserr, &neval);

	return I;
}

double gsl_qag(double from, double to, double (*func)()){
	double eps = 10e-6;
	size_t limit = 1000;
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

double gsl_qags(double from, double to, double (*func)()){
	double eps = 10e-6;
	size_t limit = 1000;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	F.function = func;
	F.params = &alpha;
	gsl_integration_qags(&F, from, to, 0, eps, limit, w, &I, &abserr);


	gsl_integration_workspace_free(w);
	return I;
}

double gsl_qagp(double from, double to, double (*func)()){
	double eps = 10e-6;
	size_t limit = 1000, npts = 2;
	gsl_integration_workspace *w = gsl_integration_workspace_alloc(limit);
	gsl_function F;
	double I, abserr, alpha;
	double pts[] = {from, to};
	F.function = func;
	F.params = &alpha;
	gsl_integration_qagp(&F, pts, npts, 0, eps, limit, w, &I, &abserr);


	gsl_integration_workspace_free(w);
	return I;
}



int main(){
	printf("my function integrated value: %f\n", int_rect(0.0, 30.0, root));
	printf("count is: %d\n", get_count());
	printf("gsl_qng integrated value: %f\n", gsl_qng(0.0, 30.0, root));
	printf("count is: %d\n", get_count());
	printf("gsl_qag integrated value: %f\n", gsl_qag(0.0, 30.0, root));
	printf("count is: %d\n", get_count());
	printf("gsl_qags integrated value: %f\n", gsl_qags(0.0, 30.0, root));
	printf("count is: %d\n", get_count());
	printf("gsl_qagp integrated value: %f\n", gsl_qagp(0.0, 30.0, root));
	printf("count is: %d\n", get_count());




	return 0;
}
