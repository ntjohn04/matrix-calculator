# matrix-calculator

## DESCRIPTION

A C++ program that includes some basic operations perfomable on matrices. Matrix.cpp is a standalone file, and MatrixDriver.cpp includes a prompt which allows the user to enter 
and perform operations on matrices by reading keyboard inputs.

## TASKS

- [x] Basic Matrix Arithmetic
  - [x] Addition
  - [x] Subtraction
  - [x] Scalar Multiplication
  - [x] Matrix Multiplication
  - [x] Exponentiation
 
- [x] Matrix Operations
  - [x] Generate n x n Identity Matrix
  - [ ] LU Decomposition
  - [ ] Transpose
  - [ ] Inverse
  - [ ] Determinant
  - [x] Row Reduction by Elementary Matrix Multiplication
    - [x] Row Echelon Form
      - [x] add s times row i to row j
      - [ ] swap rows i and j
      - [ ] multiply row i by s
    - [ ] Reduced Row Echelon Form

## DOCUMENTATION

### Matrix.cpp

The standalone class file for which the driver program runs on, and is declared in Matrix.h.

#### FUNCTIONS

Matrix::Matrix(int n, int m, int augment, string sName)<br/>

<ul>
The constructor for the Matrix object takes as parameters a number of rows and columns, an optional augmentation column (0 for none), and a name. Constructor initializes these variables and sets the size of the matrix, which is a 2-D vector, vector<vector<float>>.
</ul>
  
Matrix Matrix::AddMatrix(Matrix aMatrix, string name)<br/>

<ul>
Takes another matrix, and a new name, as parameters. It returns a new matrix with the name passed to the function. Matrices must be the same exact size in order to add. If matrices differ in size, returns the zero matrix instead.
</ul>
  
Matrix Matrix::SubtractMatrix(Matrix sMatrix, string name)<br/>
  
<ul>  
Takes another matrix, and a new name, as parameters. It returns a new matrix with the name passed to the function. Matrices must be the same exact size in order to subtract. If matrices differ in size, returns the zero matrix instead.
</ul>
  
void Matrix::MultiplyScalar(int coef)<br/>
  
<ul>
Takes one coefficient as a parameter, and multiplies it by all entries in the Matrix the function is being called from.
</ul>
  
Matrix Matrix::MultiplyMatrix(Matrix mMatrix, string name)<br/>
  
<ul>
Takes another matrix as a parameter, as well as a new name. In order to multiply, the number of columns of the first Matrix must equal the number of rows of the second Matrix. If Matrices are wrong size, returns the zero matrix. Matrix Multiplication is done by summing the product of entries incrementing in the ith and jth rows/columns of the first and second Matrix respectively.
</ul>
  
void Matrix::Exponentiate(int power)<br/>
  
<ul>
Takes a power to raise the Matrix by as a parameter. Operates on the Matrix from which the function is called, and multiplies it by itself, thus it must be a square matrix due to the row/column restraint of Matrix Multiplication. It will turn a matrix into the zero matrix if matrix is not square.
</ul>
  
Matrix Matrix::IdentityMatrix(int size)<br/>
  
<ul>
Generates a square Identity Matrix, with all entries being 0s except for 1s along the main diagonal. Creates a name "In", with n being the size. Identity Matrix is used to create Elementary Matrices for Row Reduction.
</ul>
  
vector\<Matrix> Matrix::REF()<br/>

<ul>  
Creates a vector of Matrices based on the Matrix from which the function is called. All but the back of the vector is comprised of Elementary Matrices used to obtain the Row Echelon Form of the original Matrix, which is pushed back to the end of the vector. Iterates through a double for loop. The inner loop creates a number of Elementary Matrices equal to the number of rows - the current row position of the pivot point. These Elementary Matrices, when multiplied by the given Matrix, create a column of zeroes in the position corresponding to the iteration of the outer loop. Currently does not support moving the pivot over to avoid divide by zeroes and free variables, and does not support swapping rows.
</ul>

void Matrix::InputMatrix()<br/>

<ul>
Lets the user enter the entries of the matrix row-by-row.
</ul>

void Matrix::Print()<br/>

<ul>
Prints the matrix with comma separated values, and an augmentation column if exists
</ul>

### Matrix.h

Declares variables and functions of class Matrix.cpp. 

### MatrixDriver.cpp

Includes a prompt allowing the user to create and operate on matrices during run-time. Most functions ask user for some input then call functions from Matrix.cpp. Includes a vector of Matrices to allow multiple Matrices to be loaded in memory at the same time.

## E-MAIL

ntjohn04@louisville.edu
