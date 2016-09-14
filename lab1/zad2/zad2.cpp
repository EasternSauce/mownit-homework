#include <iostream>
#include <cmath>
using namespace std;

int main(){
    float epsilon = 1;
    float prev_epsilon;

    while(epsilon + 1 > 1){
        prev_epsilon = epsilon;
        epsilon /= 2;
    }
    cout << prev_epsilon << endl;
    cout << 3.0f*(4.0f/3.0f-1.0f)-1.0f << endl;
    return 0;
}
