#ifndef DYNAMIC_UNIVARIABLE_HPP
#define DYNAMIC_UNIVARIABLE_HPP

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//tracking the position of a constant-velocity aircraft moving away from a sensor in a one dimensional world

float currentVeloEst (float veloEst, float predicted_pos, float beta, float meas, float dt){

    veloEst = veloEst + (beta * ((meas - predicted_pos) / dt));

    return veloEst;
}

float pos_extrap(float pos, float dt, float velo){
    float x_pred = pos + (velo * dt);
    return x_pred;
}

std::vector<float> dynamicKalman(float prior_x_est, float prior_velo_est, float pos_data[], float n){
    std::vector<float> state_est(2, 0);

    for (int i = 0; i < n; ++i){
        float pos_est = currentPosEst(prior_x_est, 0.2, pos_data[i]);
        float velo_est = currentVeloEst(prior_velo_est, prior_x_est, 0.1, pos_data[i], 5);

        state_est[1] = pos_est;
        state_est[2] = velo_est;
        prior_velo_est = velo_est;

        prior_x_est = pos_extrap(prior_x_est, 5, prior_velo_est);
        prior_velo_est = velo_est;
        printf("pos: %f, velo: %f\n", state_est[1], state_est[2]);
    }

    return state_est;
}

#endif