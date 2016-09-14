#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(){
	double x0, x1, x2;
	x0 = 1.0;
	x1 = 1.0/3.0;

	cout << setprecision(8);
	cout << "Pierwsza kolumna: elementy ciagu x{0} = 1, x{1} = 1/3, x{n+1} = 13/3*x{n} - 3/4*x{n-1}" << endl;
	cout << "Druga kolumna: elementy ciagu x{n} = (1/3)^n" << endl;
	cout << "Trzecia kolumna: roznica miedzy elementami" << endl;
	cout << "Wzor rekurencyjny i ogolny sa rownowazne" << endl;

	int i;
	for(i = 0; i < 35; i++){
		cout << (double)x0 << "\t";
		cout << pow(1.0/3.0, double(i)) << "\t";
		cout << abs(x0 - pow(1.0/3.0, double(i))) << endl;

		double new_x = 13.0/3.0*x1 - 4.0/3.0*x0;
		x0 = x1;
		x1 = new_x;
	}
	cout << x0 << "\t";
	cout << pow(1.0/3.0, double(i)) << "\t";
	cout << abs(x0 - pow(1.0/3.0, double(i))) << endl;
}
