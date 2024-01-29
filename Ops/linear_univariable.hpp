#ifndef LINEAR_UNIVARIABLE_HPP
#define LINEAR_UNIVARIABLE_HPP

#include <iostream>
#include <cmath>

using namespace std;


//STATE UPDATE EQUATION
//alpha = kalman gain. if alpha = 1, then sensor accuracy is presumed to be high. if alpha = 0, accuracy is low.
float currentPosEst (float predicted_state, float alpha, float meas){
    float current_state = predicted_state + (alpha * (meas - predicted_state));
    return current_state;
}

//LINEAR, UNIVARIABLE KALMAN FILTER ALGO
//tracking the weight of a bar of gold, for example or something like that
float linearKalman (float prior_est, float measurements[], float n){
    float sysStateEst;

    for (int i = 0; i < n; ++i){
        float Kn = 1/n;
        sysStateEst = currentPosEst(prior_est, Kn, measurements[i]);
        prior_est = sysStateEst;
    }

    return sysStateEst;
}

#endif
