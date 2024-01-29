#include <iostream>
#include <cmath>
#include "Ops/ops.hpp"

using namespace std;

int main (){
    int n;
    float init_guess;

    cout << "Number of measurements: " << endl;
    cin >> n;

    float measurements[n];

    cout << "Enter " << n << " measurements: " << endl;
    for (int i = 0; i < n; ++i){
        scanf("%f", &measurements[i]);
    }
    cout << "Initial guess: " << endl;
    cin >> init_guess;

    cout << "State estimate after " << n << " iterations is " << linearKalman(init_guess, measurements, float(n)) << endl;

    return 0;
}