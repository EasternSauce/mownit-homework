#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (void){
	FILE *input, *output1, *output2;
	input=fopen("wartosci.txt","w");
	int N = 1000000;
	for (int i = 0; i < N; i++){
		double x = i;
		fprintf (input,"%lf,%lf\n", x, i + 0.5 * sin (i));
	}

}

