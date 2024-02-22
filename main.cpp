#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "ABG_filter/1d_kinematic.hpp"
#include "ABG_filter/static_estimation.hpp"
#include "1_Variable_KalmanFilter/kalmanFilter.hpp"
#include "1_Variable_KalmanFilter/stat_dict.hpp"
#include "1_Variable_KalmanFilter/readFile.hpp"

using namespace std;

int main (){
    /*
    int n;
    float init_var_guess;
    float init_pos_guess;
    float dt;

    cout << "Number of measurements: " << endl;
    cin >> n;

    float pos_data[n], pos_var_data[n];

    cout << "Enter " << n << " pos measurements: " << endl;
    for (int i = 0; i < n; ++i){
        scanf("%f", &pos_data[i]);
    }

    float var_data;
    cout << "Sensor variance: " << endl;
    cin >> var_data;
    for (int i = 0; i < n; ++i){
        var_data[i] = variance(pos_data[i], n);
    }

    cout << "Initial pos guess: " << endl;
    cin >> init_pos_guess;

    cout << "Initial guess variance: " << endl;
    cin >> init_var_guess;

    float process_noise_var;
    cout << "Process noise variance: " << endl;
    cin >> process_noise_var;

    cout << "Length of time step: " << endl;
    cin >> dt;

    std::vector<float> state_vector = kalmanAlgo(init_pos_guess, init_var_guess, pos_data, var_data, process_noise_var, n, dt);
    //float final_pos = state_vector[0];
    //float final_var = state_vector[1];
    cout << "Position estimate after " << n << " iterations is " << state_vector[0] << " " << endl;
    cout << "Variance estimate after " << n << " iterations is " << state_vector[1] << " " << endl;
*/
    readFile();

    return 0;
}