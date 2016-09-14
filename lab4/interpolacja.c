#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <time.h>
#include <sys/time.h>

int N = 100;

double standard_deviation(double data[], int n)
{
	double mean=0.0, sum_deviation=0.0;
	int i;
	for(i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;
	for(i=0; i<n;++i)
		sum_deviation+=(data[i]-mean)*(data[i]-mean);
	return sqrt(sum_deviation/n);           
}

double mean(double data[], int n)
{
	double mean=0.0;
	int i;
	for(i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;
	return mean; 
}


void gsl_interpolation(double x[N], double y[N], FILE * file){
	fprintf(file, "x,y\n");
	double xi, yi;
	gsl_interp_accel * acc = gsl_interp_accel_alloc();
	gsl_spline * spline = gsl_spline_alloc (gsl_interp_akima, N);

	gsl_spline_init (spline, x, y, N);

	for (xi = x[0]; xi < x[N - 1]; xi += 0.01)
	{
		yi = gsl_spline_eval(spline, xi, acc);
		fprintf (file,"%lf,%lf\n", xi, yi);
	}
	gsl_spline_free(spline);
	gsl_interp_accel_free(acc);
}


void lagrange_interp(double x[N], double y[N], FILE * file){

	fprintf(file, "x,y\n");
	for (double xi = x[0]; xi < x[N - 1]; xi += 0.01){
		float sum, pf;
		int I, j, n = N;
		for(int i = 0; i < n; i++)
		{
			pf = 1;
			for(j = 0; j < n; j++)
			{
				if(j != i){
					pf *= (xi - x[j])/(x[i] - x[j]);
				}
			}
			sum += y[i] * pf;
		}

		double yi = sum;

		fprintf (file,"%lf,%lf\n", xi, yi);

	}

}


void newton_interp(double x[N], double y[N], FILE * file){
	fprintf(file, "x,y\n");

	for(double xi = x[0]; xi < x[N-1]; xi += 0.01){
		int MaxN = 100;
		int Order_of_diff = 4;
		double arr_x[MaxN+1], arr_y[MaxN+1], numerator=1.0, denominator=1.0, xxx, yyy, p, h, diff_table[MaxN+1][Order_of_diff+1];
		int i,j,n,k;

		n = N;

		for(i=0; i<=n; i++){
			arr_x[i] = x[i];
			arr_y[i] = y[i];
		}
		xxx = xi;
		h=arr_x[1]-arr_x[0];

		for(i=0; i<=n-1; i++)
			diff_table[i][1]=arr_y[i+1]-arr_y[i];/*Creating the difference table and calculating first order differences*/
		for(j=2; j<=Order_of_diff; j++)/*Calculating higher order differences*/
			for(i=0; i<=n-j; i++)
				diff_table[i][j]=diff_table[i+1][j-1] - diff_table[i][j-1];
		i=0;

		while(!(arr_x[i]>xxx)) /* Finding x0 */
			i++;
		i--;
		p=(xxx-arr_x[i])/h;
		yyy=arr_y[i];

		for (k=1; k<=Order_of_diff; k++)
		{
			numerator *=p-k+1;
			denominator *=k;
			yyy +=(numerator/denominator)*diff_table[i][k];
		}
		double yi = yyy;

		fprintf (file,"%lf,%lf\n", xi, yi);
	}
}

int main (void){

	int i;
	double x[100000]; 
	double y[100000];

	FILE *input; *output1, *output2, *output3;
	FILE *output;
	input=fopen("wartosci.txt","r");
	//output=fopen("gslinterp3.txt","w");

	output1=fopen("inter1.txt","w");
	output2=fopen("inter2.txt","w");
	output3=fopen("inter3.txt","w");

	for (i = 0; i < 100000; i++){
		fscanf(input, "%lf,%lf\n", &x[i], &y[i]);
	}


	gsl_interpolation(x, y, output1);
	lagrange_interp(x, y, output2);
	newton_interp(x, y, output3);

	fclose(output1);
	fclose(output2);
	fclose(output3);

	/*
	   fprintf(output, "time,n\n");
	   double deviations[10];
	   for(int n = 10; n < 100; n += 10){
	   N = n;
	   printf("measuring for N = %d\n", N);
	   double times[10];
	   for(int i = 0; i < 10; i++){
	   struct timeval start, end;
	   gettimeofday(&start, NULL);

	   gsl_interpolation(x, y, input);

	   gettimeofday(&end, NULL);

	   double elapsed = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	   times[i] = elapsed;

	//printf("elapsed: %lf\n", elapsed);
	}
	printf("mean: %lf\n", mean(times, 10));
	fprintf(output, "%lf,%d\n", mean(times, 10), n);
	printf("standard deviation: %lf\n", standard_deviation(times, 10));
	deviations[n/10-1] = standard_deviation(times, 10);
	}
	printf("mean std dev: %lf\n", mean(deviations, 10));
	*/


	fclose(input);

	return 0;
}


