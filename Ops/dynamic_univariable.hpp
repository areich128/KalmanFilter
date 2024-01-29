#include <iostream>
#include <cmath>
#include "linear_univariable.hpp"

using namespace std;

//tracking the position of a constant-velocity aircraft moving away from a sensor in a one dimensional world

float currentVeloEst (float predicted_state, float beta, float meas, float dt){
    float veloEst;

    veloEst = predicted_state * beta * ((meas - predicted_state) / dt);

    return veloEst;
}

float state_extrap(float pos, float dt, float velo){
    float x_pred = pos + (velo * dt);
    return x_pred;
}

float dynamicKalman(float prior_x_est, float prior_velo_est, float measurements[], float n){

}