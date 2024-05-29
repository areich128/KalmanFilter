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
#include "Multivariable_Kalman_Filter/uncertainty_class.hpp"

using namespace std;

int main (){
    
    const int n = 90;
    float init_var_guess;
    float init_pos_guess;
    float dt = 1;

    // float pos_data[n], pos_var_data[n];

    // cout << "Enter " << n << " pos measurements: " << endl;
    // for (int i = 0; i < n; ++i){
    //     scanf("%f", &pos_data[i]);
    // }

    // float var_data;
    // cout << "Sensor variance: " << endl;
    // cin >> var_data;
    // for (int i = 0; i < n; ++i){
    //     var_data[i] = variance(pos_data[i], n);
    // }

    // cout << "Initial pos guess: " << endl;
    init_pos_guess = 71;

    // cout << "Initial guess variance: " << endl;
    init_var_guess = 1;

    float process_noise_var = 0.1;
    // cout << "Process noise variance: " << endl;
    // cin >> process_noise_var;

    // cout << "Length of time step: " << endl;
    // cin >> dt;
    vector<float> pos_data = readFile();

    std::vector<float> state_vector = kalmanAlgo(init_pos_guess, 0.1, pos_data, init_var_guess, process_noise_var, n, dt);
    //float final_pos = state_vector[0];
    //float final_var = state_vector[1];
    // cout << "Position estimate after " << n << " iterations is " << state_vector[0] << " " << endl;
    // cout << "Variance estimate after " << n << " iterations is " << state_vector[1] << " " << endl;
    writeFile(state_vector);
    //readFile();
    // int vector_size;
    // int error_vector[5];

    // cout << "Size of vector: ";
    // cin >> vector_size;
    // cout << endl;

    // cout << "Measurements: ";
    // for (int i = 0; i < vector_size; ++i){
    //     cin >> error_vector[i];
    // }

    

    return 0;
}