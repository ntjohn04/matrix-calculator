#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

using namespace std;

Matrix::Matrix(int n, int m, int augment, string sName) {
    rows = n;
    cols = m;
    augCol = augment;
    name = sName;
    matrix.resize(rows, vector<float>(cols));
}

Matrix Matrix::AddMatrix(Matrix aMatrix, string name) {
    if (rows == aMatrix.rows && cols == aMatrix.cols && augCol == aMatrix.augCol) {
        Matrix result(rows, cols, augCol, name);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[i][j] + aMatrix.matrix[i][j];
            }
        }
        return result;
    }
    else {
        cout << "Error: Matrices Differ in Size." << endl;
        return Matrix(1, 1, 0, "zero");
    }
}

Matrix Matrix::SubtractMatrix(Matrix sMatrix, string name) {
    if (rows == sMatrix.rows && cols == sMatrix.cols && augCol == sMatrix.augCol) {
        Matrix result(rows, cols, augCol, name);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[i][j] - sMatrix.matrix[i][j];
            }
        }
        return result;
    }
    else {
        cout << "Error: Matrices Differ in Size." << endl;
        return Matrix(1, 1, 0, "zero");
    }
}

void Matrix::MultiplyScalar(int coef) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= coef;
        }
    }
}

Matrix Matrix::MultiplyMatrix(Matrix mMatrix, string name) {
    if (cols == mMatrix.rows && augCol == mMatrix.augCol) {
        Matrix result(rows, mMatrix.cols, augCol, name);
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                float element = 0;
                for (int k = 0; k < cols; k++) {
                    element += matrix[i][k] * mMatrix.matrix[k][j];
                    //cout << k << "\t" << matrix[i][k] << "\t" << mMatrix.matrix[k][j] << endl;
                }
                result.matrix[i][j] = element;
            }
        }
        return result;
    }
    else {
        cout << "Error: Matrices Differ in Size." << endl;
        return Matrix(1, 1, 0, "zero");
    }
}

void Matrix::Exponentiate(int power) {
    for (int i = 1; i < power; i++) {
        *this = MultiplyMatrix(*this, name);
    }
}

Matrix Matrix::IdentityMatrix(int size) {
    string name = "I" + to_string(size);
    cout << "made In name: " << name << endl;
    Matrix InMatrix(size, size, 0, name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) InMatrix.matrix[i][j] = 1;
            else InMatrix.matrix[i][j] = 0;
        }
    }
    cout << "returning In" << endl;
    return InMatrix;
}

Matrix Matrix::PivotRowSwap(Matrix pMatrix) {

}

vector<Matrix> Matrix::REF() {
    vector<Matrix> eleMatrices;
    eleMatrices.reserve(rows+1);
    vector<int> pivot(2, 0);
    float mul;

    Matrix result = *this;
    result.name = result.name + "(REF)";

    for (int k = 1; k < rows; k++) {
        cout << "iteration k: "<< k << endl;
        for (int i = pivot[0]; i < matrix.size()-1; i++) {
            cout << "iteration i: "<< i << endl;
            mul = -1*result.matrix[i+1][pivot[1]]/result.matrix[pivot[0]][pivot[1]];
            cout << "made mul: " << result.matrix[i+1][pivot[1]] << " / " << result.matrix[pivot[0]][pivot[1]] << endl;
            eleMatrices.push_back(IdentityMatrix(rows));
            eleMatrices.back().Print();
            eleMatrices.back().matrix[i+1][k-1] = mul;
            cout << "made Elementary Matrix" << endl;
            eleMatrices.back().Print();
            cout << "multiplied" << endl;
            result = eleMatrices.back().MultiplyMatrix(result, result.name);
            result.Print();
            //result = MultiplyMatrix(eleMatrices[k], result.name);
            cout << "pushed result" << endl;
        }
        pivot[0]++;
        pivot[1]++;
    }
    eleMatrices.push_back(result);
    return eleMatrices;
}

void Matrix::InputMatrix() {
    for (int i = 0; i < rows; i++) {
        cout << "Enter row " << i+1 << endl;
        for (int j = 0; j < cols; j++) {
            scanf("%f", &matrix[i][j]);
        }
        cout << endl;
    }
}

void Matrix::Print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j];
            if (j != cols-1 && j != augCol-2) cout << ", ";
            if (j == augCol-2) cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}
