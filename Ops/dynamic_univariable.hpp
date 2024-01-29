#ifndef DYNAMIC_UNIVARIABLE_HPP
#define DYNAMIC_UNIVARIABLE_HPP

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//tracking the position of a constant-velocity aircraft moving away from a sensor in a one dimensional world

float currentVeloEst (float predicted_velo, float beta, float meas, float dt){
    float veloEst;

    veloEst = predicted_velo * beta * ((meas - predicted_velo) / dt);

    return veloEst;
}

float state_extrap(float pos, float dt, float velo){
    float x_pred = pos + (velo * dt);
    return x_pred;
}

std::vector<float> dynamicKalman(float prior_x_est, float prior_velo_est, float pos_meas[], float velo_meas[], float n){
    std::vector<float> state_est(n);

    for (int i = 0; i < n; ++i){
        float pos_est = currentPosEst(prior_x_est, 0.2, pos_meas[i]);
        float velo_est = currentVeloEst(prior_velo_est, 0.1, velo_meas[i], 1);
        prior_x_est = state_extrap(prior_x_est, 1, prior_velo_est);
        prior_velo_est = velo_est;
        state_est[1] = prior_x_est;
        state_est[2] = prior_velo_est;

    }

    return state_est;
}

#endif