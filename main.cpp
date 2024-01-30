#include <iostream>
#include <cmath>
#include <vector>

#include "ABG_filter/1d_kinematic.hpp"
#include "ABG_filter/static_estimation.hpp"
#include "KalmanFilter/kalmanFilter.hpp"
#include "KalmanFilter/stat_dict.hpp"

using namespace std;

int main (){
    int n;
    float init_velo_guess;
    float init_pos_guess;
    float init_acc_guess;
    float dt;

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

    cout << "Initial acceleration guess: " << endl;
    cin >> init_acc_guess;

    cout << "Length of time step: " << endl;
    cin >> dt;

    std::vector<float> state_vector = dynamicKalman(init_pos_guess, init_velo_guess, init_acc_guess, pos_meas, n, dt);

    cout << "Position estimate after " << n << " iterations is " << state_vector[1] << " " << endl;
    cout << "Velocity estimate after " << n << " iterations is " << state_vector[2] << " " << endl;

    return 0;
}