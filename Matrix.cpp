#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

#include <iomanip>

#include <fstream>
#include <sstream>

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
    Matrix InMatrix(size, size, 0, name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) InMatrix.matrix[i][j] = 1;
            else InMatrix.matrix[i][j] = 0;
        }
    }
    return InMatrix;
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
        cout << "pivot: " << pivot[0] << ", " << pivot[1] << "; value: " << result.matrix[pivot[0]][pivot[1]] << endl;
        for (int i = pivot[0]; i < matrix.size()-1; i++) {
            cout << "iteration i: "<< i << endl;
            mul = -1*result.matrix[i+1][pivot[1]]/result.matrix[pivot[0]][pivot[1]];
            cout << "made mul: " << result.matrix[i+1][pivot[1]] << " / " << result.matrix[pivot[0]][pivot[1]] << endl;
            eleMatrices.push_back(IdentityMatrix(rows));
            eleMatrices.back().matrix[i+1][k-1] = mul;
            cout << "made Elementary Matrix" << endl;
            eleMatrices.back().Print();
            cout << "multiplied" << endl;
            result = eleMatrices.back().MultiplyMatrix(result, result.name);
            //result.Print();
            //result = MultiplyMatrix(eleMatrices[k], result.name);
            cout << "pushed result" << endl;
        }
        pivot[0]++;
        pivot[1]++;
        if (result.matrix[pivot[0]][pivot[1]] == 0 && pivot[0] != rows) {
            cout << "pivot is 0! swapping!" << endl;
            int i = 1;
            while (result.matrix[pivot[0]][pivot[1]] == 0 && pivot[0]+i != rows) {
                result.Print();
                cout << "swappings rows " << pivot[0]+1 << " and " << pivot[0]+1+i << endl;
                result.matrix[pivot[0]].swap(result.matrix[pivot[0]+i]);
                eleMatrices.push_back(IdentityMatrix(rows));
                eleMatrices.back().matrix[pivot[0]].swap(eleMatrices.back().matrix[pivot[0]+i]);
                i++;
            }
            if (pivot[0]+i == rows) {
                cout << "free variable at column " << pivot[1]+1 << endl;
                pivot[1]++;
            }
            result.Print();
        }
        if (result.matrix[pivot[0]][pivot[1]] == 0) {
            cout << "broken" << endl;
            break;
        }
    }
    eleMatrices.push_back(result);
    return eleMatrices;
}

Matrix Matrix::TransposeMatrix() {
    Matrix result(cols, rows, 0, name + "(T)");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[j][i];
        }
    }
    return result;
}

Matrix Matrix::Cofactor(Matrix cMatrix, int col) {
    Matrix subMatrix(cMatrix.rows-1, cMatrix.cols-1, 0, "sub" + to_string(col));
    for (int i = 1; i < cMatrix.rows; i++) {
        for (int j = 0; j < cMatrix.cols; j++) {
            if (j == col) continue;
            if (j < col) {
                subMatrix.matrix[i-1][j] = cMatrix.matrix[i][j];
            }
            else {
                subMatrix.matrix[i-1][j-1] = cMatrix.matrix[i][j];
            }
        }
    }
    return subMatrix;
}

int Matrix::Det(Matrix dMatrix) {
    if (dMatrix.rows == 2) {
        return dMatrix.matrix[0][0] * dMatrix.matrix[1][1] - dMatrix.matrix[0][1] * dMatrix.matrix[1][0];
    }
    else {
        int result = 0;
        for (int k = 0; k < dMatrix.cols; k++) {
            Matrix subMatrix = Cofactor(dMatrix, k);
            result += dMatrix.matrix[0][k] * pow(-1, k) * Det(subMatrix);
        }
        return result;
    }
}

int Matrix::Determinant() {
    if (rows == cols) {
        return Det(*this);
    }
    else {
        cout << "Error: Matrix Must Be Square." << endl;
        return -1;
    }
}

void Matrix::SaveCSV(string FilePath) {
    ofstream mSave(FilePath);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mSave << matrix[i][j];
            if (j != cols-1) mSave << ", ";
        }
        mSave << "\n";
    }
}

void Matrix::UploadCSV(string FilePath) {
    //FILE* mUpload = fopen(FilePath.c_str(), "r");
    ifstream mGetter(FilePath);

    rows = 0;
    cols = 0;
    
    string line;
    getline(mGetter, line);
    cout << line << endl;

    stringstream sm(line);
    while (getline(sm, line, ',')) {
        cols++;
    }

    while (mGetter.good()){
        getline(mGetter, line);
        if (line.length() != 0) rows++;
    }
    rows++;

    cout << rows << " " << cols << endl;
    mGetter.close();
    
    ifstream mUpload(FilePath);
    cout << FilePath << endl;

    while (getline(mUpload, line)) {
        stringstream ss(line);
        vector<float> row;
        string data;

        while (getline(ss, data, ',')) {
            row.push_back(stof(data));
            cout << stof(data) << ", ";
        }
        cout << endl;
        if (row.size() > 0) matrix.push_back(row);
    }

    mUpload.close();
    
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
    cout << setprecision(5);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(8) << matrix[i][j];
            if (j != cols-1 && j != augCol-2) cout << ", ";
            if (j == augCol-2) cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}
