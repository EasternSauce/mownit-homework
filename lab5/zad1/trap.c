#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define begin 0
#define end 1

double func1(double x) {
	return x*x;
}

double func2(double x) {
	return sqrt(x);
}

int main(int argc, char *argv[]) {
	double eps = 10e-6;
	int op;
	if(argc > 1)
		op = atoi(argv[1]);
	int prec = 1;
	double I = 0;
	switch(op) {
		case 1:
			while(fabs(((double)1/3) - I) > eps) {
				I = 0;
				double dx = (end - begin) / (double)prec;
				for(int i = 1; i < prec; i++) {
					I += func1(begin + (dx * i));
				}	
				I += (func1(begin) + func1(end))/2;
				I *= dx;
				prec++; 	
			}			
			break;
		case 2:
			while(fabs(((double)2/3) - I) > eps) {
				I = 0;
				double dx = (end - begin) / (double)prec;
				for(int i = 1; i < prec; i++) {
					I += func2(begin + (dx * i));
				}
				I += (func2(begin) + func2(end))/2;
				I *= dx; 
				prec++;
			}
			break;
		default:
			while(fabs(((double)1/2) - I) > eps) {
				I = 0;
				double dx = (end - begin) / (double)prec;
				for(int i = 1; i < prec; i++) {
					I += begin + (dx * i);
				}
				I += (begin + end) / 2;
				I *= dx;
				prec++;
			}
			break;
	}
	printf("I(f) = %.20lf\tn = %d\n", I, prec);
	return 0;
}
