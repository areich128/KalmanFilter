#include "univariateFilter.h"

uniFilter::uniFilter(){}

uniFilter::uniFilter(vector<float> dataset){
    _dataset = dataset;
}

uniFilter::uniFilter(float initial_position, float initial_pos_var, vector<float> dataset, float sensor_var, float noise_var, float dt){
    _initial_position = initial_position;
    _initial_position_variance = initial_pos_var;
    _dataset = dataset;
    _sensor_variance = sensor_var;
    _procedural_noise_variance = noise_var;
    _dt = dt;
}


void uniFilter::setInitPositionGuess(float guess){_initial_position = guess;}
float uniFilter::getInitPositionGuess(){return _initial_position;}

void uniFilter::setInitPositionVariance(float guess){_initial_position_variance = guess;}
float uniFilter::getInitPositionVariance(){return _initial_position_variance;}

void uniFilter::setSensorVariance(float sensvar){_sensor_variance = sensvar;}
float uniFilter::getSensorVariance(){return _sensor_variance;}

void uniFilter::setProceduralNoiseVar(float noisevar){_procedural_noise_variance = noisevar;}
float uniFilter::getProceduralNoiseVar(){return _procedural_noise_variance;}

void uniFilter::setDt(float time){_dt = time;}
float uniFilter::getDt(){return _dt;}


bool uniFilter::loadData(string filename){}
vector<float> uniFilter::filter(){}
float uniFilter::findKn(){}