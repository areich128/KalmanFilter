#ifndef UNIVARIATEFILTER_H
#define UNIVARIATEFILTER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class uniFilter {
    private:

        float _initial_position;
        vector<float> _dataset;
        vector<float> _filtered_data;
        float _dt;

        float _initial_position_variance;
        float _sensor_variance;
        float _procedural_noise_variance;


    public:
        uniFilter();
        uniFilter(vector<float> dataset);
        uniFilter::uniFilter(float initial_position, float initial_pos_var, vector<float> dataset, float sensor_var, float noise_var, float dt);

        //SETTERS AND GETTERS
        void setFilteredData(vector<float> filtered_data);
        vector<float> getFilteredData();

        void setDataset(vector<float> dataset);
        vector<float> getDataset();

        void setInitPositionGuess(float guess);
        float getInitPositionGuess();

        void setInitPositionVariance(float);
        float getInitPositionVariance();

        void setSensorVariance(float);
        float getSensorVariance();

        void setProceduralNoiseVar(float);
        float getProceduralNoiseVar();

        void setDt(float time);
        float getDt();

        // FUNCTIONS
        bool loadData(string filename);
        vector<float> filter();
        float findKn(float predicted_variance, float measured_variance);

};



#endif

