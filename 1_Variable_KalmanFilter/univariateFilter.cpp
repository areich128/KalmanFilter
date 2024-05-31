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


bool uniFilter::loadData(string filename){
    ifstream inputFile(filename);

    if (!inputFile.is_open()){
        cout << "Error opening file" << endl;
        return 0;
    }

    string line;
    while (getline(inputFile, line)){
        // cout << line << "------------------" << endl;
        double data_point;

        data_point = stod(line);

        _dataset.push_back(data_point);
    }
    inputFile.close();

    return 1;
}

vector<float> uniFilter::filter(){
    

}

float uniFilter::findKn(float predicted_variance, float measured_variance){
    float Kn = predicted_variance / (predicted_variance + measured_variance);
    return Kn;
}