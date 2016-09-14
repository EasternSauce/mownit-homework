//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

void interp(double x[9], double y[9], const gsl_interp_type *type, FILE *file, FILE *sumdiffs){
	double xi, yi;
	gsl_interp_accel *acc 
		= gsl_interp_accel_alloc ();
	gsl_spline *spline 
		= gsl_spline_alloc (type, 9);

	gsl_spline_init (spline, x, y, 9);

	double diffsum1 = 0;
	double diffsum64 = 0;
	for (xi = x[0]; xi < x[8]; xi += 0.01)
	{
		yi = gsl_spline_eval (spline, xi, acc);
		fprintf (file,"%g %g\n", xi, yi);

		if(xi >= 0 && xi < 1) diffsum1 += fabs(sqrt(xi) - yi);
		if(xi >= 0 && xi < 64) diffsum64 += fabs(sqrt(xi) - yi);
	}
	gsl_spline_free (spline);
	gsl_interp_accel_free(acc);

	fprintf(sumdiffs, "dla przedzialu od 0 do 1 suma roznic wartosci wynosi %lf\n", diffsum1);
	fprintf(sumdiffs, "dla przedzialu od 0 do 64 suma roznic wartosci wynosi %lf\n", diffsum64);
	
}


int main (void){
	int i;
	double x[9] = {0,1,4,9,16,25,36,49,64};
	double y[9] = {0,1,2,3,4,5,6,7,8};

	FILE *input, *output1, *output2, *sumdiffs;
	input=fopen("wartosci.txt","w");
	output1=fopen("inter1.txt","w");
	output2=fopen("inter2.txt","w");
	sumdiffs=fopen("sumdiffs.txt", "w");
	//  printf ("#m=0,S=2\n");

	for (i = 0; i < 9; i++)
	{
		fprintf (input,"%g %g\n", x[i], y[i]);
	}

	//  printf ("#m=1,S=0\n");
	interp(x, y, gsl_interp_polynomial, output1, sumdiffs);
	interp(x, y, gsl_interp_cspline, output2, sumdiffs);

	return 0;
}


