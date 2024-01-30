#ifndef DYNAMIC_UNIVARIABLE_HPP
#define DYNAMIC_UNIVARIABLE_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "static_estimation.hpp"

using namespace std;

//tracking the position of a constant-velocity aircraft moving away from a sensor in a one dimensional world

float currentVeloEst (float veloEst, float predicted_pos, float beta, float meas, float dt){
    veloEst = veloEst + (beta * ((meas - predicted_pos) / dt));
    
    return veloEst;
}

float currentAccEst (float accEst, float predicted_pos, float gamma, float meas, float dt){
    accEst + (gamma * ((meas - predicted_pos)/(0.5*(dt*dt))));

    return accEst;
}

float pos_extrap(float pos, float dt, float velo, float acc){
    float x_pred = pos + (velo * dt) + (0.5 * acc * (dt * dt));
    return x_pred;
}

float velo_extrap(float velo, float acc, float dt){
    float velo_pred = velo + (acc * dt);

    return velo_pred;
}

std::vector<float> dynamicKalman(float prior_x_est, float prior_velo_est, float prior_acc_est, float pos_data[], float n, float dt){
    std::vector<float> state_est(3, 0);

    for (int i = 0; i < n; ++i){
        float pos_est = currentPosEst(prior_x_est, 0.2, pos_data[i]);
        float velo_est = currentVeloEst(prior_velo_est, prior_x_est, 0.1, pos_data[i], dt);
        float acc_est = currentAccEst(prior_acc_est, prior_x_est, 0.1, pos_data[i], dt);

        state_est[1] = pos_est;
        state_est[2] = velo_est;
        state_est[3] = acc_est;

        prior_x_est = pos_extrap(prior_x_est, dt, prior_velo_est, prior_acc_est);
        prior_velo_est = velo_extrap(velo_est, acc_est, dt);
        prior_acc_est = acc_est;
        printf("pos: %f, velo: %f, acc: %f\n", state_est[1], state_est[2], state_est[3]);
    }

    return state_est;
}

#endif