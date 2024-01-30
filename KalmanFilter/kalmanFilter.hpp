#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "stat_dict.hpp"
#include "dynamics.hpp"

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

std::vector<float> filterAlgo (float obs_variance, float obs_state, float dt){
    std::vector<float> output (2, 0);
    float est_pos_var, est_velo_var, meas_pos_var, meas_pos, est_pos, est_velo;
    
    //step 1: UPDATE
    //1.1, calculate kalman gain using KALMAN GAIN equation
    float Kn = kalmanGain(est_pos_var, obs_variance);
    //1.2, update estimated state using STATE UPDATE equation
    est_pos = est_pos + Kn * (obs_state - est_pos);
    //1.3, update estimated position variance using COVARIANCE UPDATE equation
    est_pos_var = (1 - Kn) * (est_pos_var);
    output[0] = est_pos;
    output[1] = est_pos_var;

    //step 2: PREDICT
    //2.1, predict state and variance using STATE/COVARIANCE EXTRAPOLATION equations
    est_pos = estPosUpdate(est_pos, est_velo, dt);
    est_pos_var = estPosVarUpdate(est_pos_var, est_velo_var, dt);

}

#endif