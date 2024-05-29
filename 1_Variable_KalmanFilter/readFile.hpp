#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

vector<float> readFile(){
    
    ifstream inputFile("output.txt");

    if (!inputFile.is_open()){
        cout << "Error opening file" << endl;
        vector<float> error;
        error.push_back(0);
        return error;
    }

    vector<float> dataset;

    string line;
    while (getline(inputFile, line)){
        cout << line << "------------------" << endl;
        double data_point;

        data_point = stod(line);

        dataset.push_back(data_point);
    }

    inputFile.close();

    cout << "Numerical digits in the file: ";
    for (int i = 0; i < dataset.size(); ++i){
        cout << dataset.at(i) << " ";
    }
    cout << endl;

    return dataset;
}

void writeFile(vector<float> newdata){
    ofstream file_out("filtered.txt");

    if (!file_out.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    for (int i = 0; i < newdata.size(); ++i){
        file_out << newdata.at(i) << endl;
    }

    file_out.close();

    return;
}

#endif