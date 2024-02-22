#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "stat_dict.hpp"
#include "dynamics.hpp"

/*
std::vector<float> initFilter(float init_pos, float init_pos_var, float init_velo, float init_velo_var, float dt){
    std::vector<float> initEst (2, 0);
    //INITIALIZE kalman algorithm here
    //calculate predicted state for next iteration using system dynamics
    float est_pos_var, est_velo_var, meas_pos_var, meas_pos, est_pos, est_velo;
    est_pos = estPosUpdate(init_pos, init_velo, dt);
    est_pos_var = estPosVarUpdate(init_pos_var, init_velo_var, dt);
    initEst[0] = est_pos;
    initEst[1] = est_pos_var;
    return initEst;
}
*/

std::vector<float> kalmanAlgo (float init_pos, float init_pos_var, float pos_data[], float sens_var_data, float proc_n_var, float n, float dt){
    std::vector<float> output (2, 0);
    float est_pos_var, est_velo_var, meas_pos_var, meas_pos, est_pos, est_velo;

    //step 0: INITIALIZE kalman algorithm here
    //calculate predicted state for next iteration using system dynamics
    //here we are using constant dynamics (i.e., the true value does not change)
    est_pos = init_pos;
    est_pos_var = init_pos_var;
    
    for (int i = 0; i < n; ++i){

        //step 1: UPDATE
        //1.1, calculate kalman gain using KALMAN GAIN equation
        float Kn = kalmanGain(est_pos_var, sens_var_data);
        //1.2, update estimated state using STATE UPDATE equation
        est_pos = est_pos + (Kn * (pos_data[i] - est_pos));
        //1.3, update estimated position variance using COVARIANCE UPDATE equation
        est_pos_var = (1 - Kn) * (est_pos_var);
        std::cout << est_pos << "   " << est_pos_var << std::endl;
        output[0] = est_pos;
        output[1] = est_pos_var;
        
        //step 2: PREDICT
        //Because there is process noise, the variance is changed a bit.
        est_pos_var = est_pos_var + proc_n_var;
        //2.1, predict state and variance using STATE/COVARIANCE EXTRAPOLATION equations
        //est_pos = estPosUpdate(est_pos, est_velo, dt);
        //est_pos_var = estPosVarUpdate(est_pos_var, est_velo_var, dt);
    }
    return output;
}

#endif