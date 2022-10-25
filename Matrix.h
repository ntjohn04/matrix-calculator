#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <string>
#include <vector>

using namespace std;

class Matrix {
    public:
    Matrix(int n,  int m,  int augment,  string sName);
    vector<vector<float>> matrix;
    string name;
    int rows;
    int cols;

    int augCol;

    Matrix AddMatrix(Matrix aMatrix,  string name);
    Matrix SubtractMatrix(Matrix sMatrix,  string name);
    void MultiplyScalar(int coef);
    Matrix MultiplyMatrix(Matrix mMatrix,  string name);
    void Exponentiate(int power);

    Matrix IdentityMatrix(int size);
    vector<Matrix> REF();
    Matrix Cofactor(Matrix cMatrix,  int col);
    int Det(Matrix dMatrix);
    int Determinant();

    void SaveCSV(string FilePath);
    void UploadCSV(string FilePath);

    Matrix TransposeMatrix();

    void InputMatrix();
    void Print();
};
