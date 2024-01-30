#ifndef DYNAMICS_HPP
#define DYNAMICS_HPP

#include <iostream>
#include <cmath>

//constant velocity dynamics. Optimize later to include acceleration.
float estPosUpdate (float init_pos, float init_velo, float dt){
    float pos_update = init_pos + (init_velo * dt);
    return pos_update;
}

float estPosVarUpdate (float init_pos_var, float init_velo_var, float dt){
    float pos_var = init_pos_var + (dt * dt * init_velo_var);
    return pos_var;
}

#endif