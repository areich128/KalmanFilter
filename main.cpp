#include <iostream>
#include <cmath>
#include <vector>
#include "Ops/linear_univariable.hpp"
#include "Ops/dynamic_univariable.hpp"

using namespace std;

int main (){
    int n;
    float init_velo_guess;
    float init_pos_guess;

    cout << "Number of measurements: " << endl;
    cin >> n;

    float pos_meas[n], velo_meas[n];

    cout << "Enter " << n << " pos measurements: " << endl;
    for (int i = 0; i < n; ++i){
        scanf("%f", &pos_meas[i]);
    }
    cout << "Initial pos guess: " << endl;
    cin >> init_pos_guess;

    cout << "Initial velo guess: " << endl;
    cin >> init_velo_guess;

    std::vector<float> state_vector = dynamicKalman(init_pos_guess, init_velo_guess, pos_meas, n);

    cout << "Position estimate after " << n << " iterations is " << state_vector[1] << " " << endl;
    cout << "Velocity estimate after " << n << " iterations is " << state_vector[2] << " " << endl;

    return 0;
}