#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_fit.h>

int main (int argc, char * argv[]){

	FILE *input;
	FILE *output;
	input=fopen("output.txt","r");
	output=fopen("ls.txt","w");

	double x[100];
	double y[100];
	double w[100];

	fscanf(input, "%*[^\n]\n", NULL);
	int c = 0;
	while (!feof(input)){
		double xval;
		double yval;
		fscanf(input, "%lf,%lf\n", &xval, &yval);
		x[c] = xval;
		y[c] = yval;
		w[c] = 1;
		c++;
	}
	int n = c;

	double c0, c1, cov00, cov01, cov11, chisq;

	gsl_fit_wlinear (x, 1, w, 1, y, 1, n, 
			&c0, &c1, &cov00, &cov01, &cov11, 
			&chisq);

	fprintf(output, "c0,c1\n");
	fprintf(output, "%lf,%lf\n", c0, c1);

	printf ("# best fit: Y = %g + %g X\n", c0, c1);
	printf ("# covariance matrix:\n");
	printf ("# [ %g, %g\n#   %g, %g]\n", 
			cov00, cov01, cov01, cov11);
	printf ("# chisq = %g\n", chisq);

	for (int i = 0; i < n; i++)
		printf ("data: %g %g %g\n", 
				x[i], y[i], 1/sqrt(w[i]));

	printf ("\n");

	for (int i = -30; i < 130; i++)
	{
		double xf = x[0] + (i/100.0) * (x[n-1] - x[0]);
		double yf, yf_err;

		gsl_fit_linear_est (xf, 
				c0, c1, 
				cov00, cov01, cov11, 
				&yf, &yf_err);

		printf ("fit: %g %g\n", xf, yf);
		printf ("hi : %g %g\n", xf, yf + yf_err);
		printf ("lo : %g %g\n", xf, yf - yf_err);
	}
	fclose(input);
	fclose(output);
	return 0;
}
