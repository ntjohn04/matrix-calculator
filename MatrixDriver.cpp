#include "Matrix.h"

#include <string.h>

using namespace std;

vector<Matrix> MatrixList;
bool loop = true;

void CreateMatrix() {
    int n;
    int m;
    int augCol;
    string name;
    cout << "Enter # of rows and columns" << endl;
    scanf("%d", &n);
    scanf("%d", &m);
    cout << endl << "Augmentation column (inclusive -- 0 for none)" << endl;
    scanf("%d", &augCol);
    cout << endl;

    MatrixList.push_back(Matrix(n, m, augCol, "temp"));
    MatrixList.back().InputMatrix();
    cout << "Enter name: " << endl;
    cin >> name;
    cout << endl;
    MatrixList.back().name = name;
}

void DeleteMatrix() {
    cout << "Select Matrix To Delete (Count: " << MatrixList.size() << ")" << endl;
    string sSel;
    cin >> sSel;

    int index;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel == MatrixList[i].name) index = i;
    }
    MatrixList.erase(MatrixList.begin()+index);
    cout << endl << "Matrix Deleted." << endl << endl;
}

void ListMatrices() {
    cout << endl;
    for (int i = 0; i < MatrixList.size(); i++) {
        cout << i+1 << ")\t" << MatrixList[i].name << endl;
    }
    cout << endl << "Press Enter To Continue" << endl;
    cin.get();
    cin.get();
}

void PrintMatrix() {
    cout << "Select Matrix To Print (Count: " << MatrixList.size() << ")" << endl;
    string sSel;
    cin >> sSel;
    cout << endl;

    int index;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel == MatrixList[i].name) index = i;
    }
    MatrixList[index].Print();
}

void AddMatrices() {
    cout << "Select Matrices To Add:" << endl;
    string sSel1, sSel2, name;
    cin >> sSel1 >> sSel2;
    cout << endl << "Enter Matrix Name:" << endl;
    cin >> name;
    cout << endl;

    int index1;
    int index2;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel1 == MatrixList[i].name) index1 = i;
        if (sSel2 == MatrixList[i].name) index2 = i;
    }
    MatrixList.push_back(MatrixList[index1].AddMatrix(MatrixList[index2], name));
}

void SubtractMatrices() {
    cout << "Select Matrices To Subtract:" << endl;
    string sSel1, sSel2, name;
    cin >> sSel1 >> sSel2;
    cout << endl << "Enter Matrix Name:" << endl;
    cin >> name;
    cout << endl;

    int index1;
    int index2;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel1 == MatrixList[i].name) index1 = i;
        if (sSel2 == MatrixList[i].name) index2 = i;
    }
    MatrixList.push_back(MatrixList[index1].SubtractMatrix(MatrixList[index2], name));
}

void ScalarMultiplication() {
    cout << "Select Matrix To Multiply:" << endl;
    string sSel;
    cin >> sSel;
    int iCoef;
    cout << endl << "Enter Scalar:" << endl;
    cin >> iCoef;

    int index;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel == MatrixList[i].name) index = i;
    }
    MatrixList[index].MultiplyScalar(iCoef);
}

void MultiplyMatrices() {
    cout << "Select Matrices To Multiply:" << endl;
    string sSel1, sSel2, name;
    cin >> sSel1 >> sSel2;
    cout << endl << "Enter Matrix Name:" << endl;
    cin >> name;
    cout << endl;

    int index1;
    int index2;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel1 == MatrixList[i].name) index1 = i;
        if (sSel2 == MatrixList[i].name) index2 = i;
    }
    MatrixList.push_back(MatrixList[index1].MultiplyMatrix(MatrixList[index2], name));
}

void ExponentiateMatrix() {
    cout << "Select Matrix To Exponentiate:" << endl;
    string sSel;
    cin >> sSel;
    int iPower;
    cout << endl << "Enter Power:" << endl;
    cin >> iPower;

    int index;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel == MatrixList[i].name) index = i;
    }
    MatrixList[index].Exponentiate(iPower);
}

void RowEchelonForm() {
    cout << "Select Matrix To Reduce To REF:" << endl;
    string sSel;
    cin >> sSel;

    int index;
    for (int i = 0; i < MatrixList.size(); i++) {
        if (sSel == MatrixList[i].name) index = i;
    }
    MatrixList.push_back(MatrixList[index].REF().back());
}

void GenerateIdentityMatrix() {
    cout << "Enter Size Of Identity Matrix: " << endl;
    int iSel;
    cin >> iSel;

    MatrixList.push_back(MatrixList[0].IdentityMatrix(iSel));
}

void Prompt() {
    cout << "Enter Selection" << endl;
    cout << "\t1) Create Matrix" << endl;
    cout << "\t2) Delete Matrix" << endl;
    cout << "\t3) List Matrices" << endl;
    cout << "\t4) Print Matrix" << endl;
    cout << "\t5) Add Matrices" << endl;
    cout << "\t6) Subtract Matrices" << endl;
    cout << "\t7) Scalar Multiplication" << endl;
    cout << "\t8) Multiply Matrices" << endl;
    cout << "\t9) Exponentiate Matrix" << endl;
    cout << "\t10) Row Echelon Form" << endl;
    cout << "\t11) Generate Identity Matrix" << endl;
    cout << "\t12) LU Decomposition" << endl;
    cout << "\t13) Exit" << endl;
    int iSel;
    scanf("%d", &iSel);
    switch (iSel) {
        case 1:
            CreateMatrix();
            break;
        case 2:
            DeleteMatrix();
            break;
        case 3:
            ListMatrices();
            break;
        case 4:
            PrintMatrix();
            break;
        case 5:
            AddMatrices();
            break;
        case 6:
            SubtractMatrices();
            break;
        case 7:
            ScalarMultiplication();
            break;
        case 8:
            MultiplyMatrices();
            break;
        case 9:
            ExponentiateMatrix();
            break;
        case 10:
            RowEchelonForm();
            break;
        case 11:
            GenerateIdentityMatrix();
            break;
        case 12:
            cout << "NOT AVAILABLE YET, SORRY CHECK REPO LATER" << endl;
            break;
        case 13:
            loop = false;
            break;
    }
}

int main(int argc, char *argv[]) {
    fflush(stdin);
    cout << "Matrix Calculator" << endl << endl;
    while(loop) {
        Prompt();
    }
    return 0;
}