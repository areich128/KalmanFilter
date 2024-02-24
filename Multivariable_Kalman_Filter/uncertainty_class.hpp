#ifndef UNCERTAINTY_CLASS_HPP
#define UNCERTAINTY_CLASS_HPP

#include <iostream>
#include <cmath>

class uncertaintyMatrix{
private:
    int rows;
    int cols;
    int **arr;

public:
    uncertaintyMatrix(int rows, int cols) : rows(rows), cols(cols) {
        arr = new int*[rows];
        for (int i = 0; i < rows; ++i){
            arr[i] = new int[cols];
        }

        for (int i = 0; i < rows; ++ i){
            for (int j = 0; j < cols; ++j){
                arr[i][j] = 0;
            }
        }
    }

    void setValue(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            arr[row][col] = value;
        }
    }

    int getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return arr[row][col];
        } else {
            return 0;
        }
    }

    ~uncertaintyMatrix(){
        for (int i = 0; i < rows; ++i){
            delete[] arr[i];
        }
        delete[] arr;
    }

};

#endif