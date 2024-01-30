#ifndef STAT_DICT_HPP
#define STAT_DICT_HPP

#include <iostream>
#include <cmath>

float mean(float point, float prev_mean, float n){
    float mean = (prev_mean + point)/n;
    return mean;
}

//only problem is how do we know n? 
float variance(float meas_state, int n){
    float variance, sum, calc_mean;
    for (int i = 0; i < n; ++i){
        calc_mean = mean(meas_state, calc_mean, n);
        sum += ((meas_state - calc_mean) * (meas_state - calc_mean));
    }
    variance = (1/(n-1)) * sum;
    return variance;
}

float stdDev(float variance){
    float std_dev = sqrt(variance);
    return std_dev;
}

float kalmanGain(float extrap_est_variance, float meas_variance){
    float Kn = extrap_est_variance / (extrap_est_variance + meas_variance);
    return Kn;
}

#endif