#include <iostream>
#include <cmath>
using namespace std;

int main(){
	float fx = 0.01;
	double dx = 0.01;

	for(int i = 0; i < 30; i++){
		cout << i << " " << fx << " " << dx << endl;
		fx = fx+3*fx*(1-fx);
		dx = dx+3*dx*(1-dx);
	}
}

