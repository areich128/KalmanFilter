#include <iostream>
#include <cmath>

using namespace std;

int e_val (int prev_pred, int pres_meas){
    int expected_val;

    expected_val = (prev_pred + pres_meas) / 2;

    return expected_val;
}