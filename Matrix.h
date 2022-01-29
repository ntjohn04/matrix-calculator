#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

using namespace std;

class Matrix {
    public:
    Matrix(int n, int m, int augment, string sName);
    vector<vector<float>> matrix;
    string name;
    int rows;
    int cols;

    int augCol;

    Matrix AddMatrix(Matrix aMatrix, string name);
    Matrix SubtractMatrix(Matrix sMatrix, string name);
    void MultiplyScalar(int coef);
    Matrix MultiplyMatrix(Matrix mMatrix, string name);
    void Exponentiate(int power);

    Matrix IdentityMatrix(int size);
    Matrix PivotRowSwap(Matrix pMatrix);
    vector<Matrix> REF();

    void InputMatrix();
    void Print();
};
