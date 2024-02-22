#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int readFile (){
    
    ifstream inputFile("datafile.txt");

    if (inputFile.is_open()){
        cerr << "Error opening file" << endl;
        return 1;
    }

    vector<int> dataset;

    char character;
    while (inputFile.get(character)){
        if (isdigit(character)){
            dataset.push_back(character - '0');
        }

    }

    inputFile.close();

    cout << "Numerical digits in the file: ";
    for (int digit : dataset){
        cout << digit << " ";
    }
    cout << endl;

    return 0;
}

#endif