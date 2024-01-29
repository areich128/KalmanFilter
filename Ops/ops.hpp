#include <iostream>
#include <cmath>

using namespace std;

int e_val (int prev_pred, int pres_meas){
    int expected_val;

    expected_val = (prev_pred + pres_meas) / 2;

    return expected_val;
}

//STATE UPDATE EQUATION
//alpha = kalman gain
float currentStateEst (float predicted_state, float alpha, float meas){
    float current_state = predicted_state - (alpha * (predicted_state - meas));
    return current_state;
}

//LINEAR, UNIVARIABLE KALMAN FILTER ALGO
float linearKalman (float prior_est, float measurements[], float n){
    float sysStateEst;

    for (int i = 0; i < n; ++i){
        float Kn = 1/n;
        sysStateEst = currentStateEst(prior_est, Kn, measurements[i]);
        prior_est = sysStateEst;
    }

    return sysStateEst;
}