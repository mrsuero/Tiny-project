#include "../include/matrix.h"

// Constructor & Destructor
Matrix::Matrix(int numRows, int numCols)
    : mNumRows(numRows), mNumCols(numCols) {
    assert(numRows > 0 && numCols > 0);
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]{};
    }
}

Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

// Accessors
int Matrix::getNumRows() const {
    return mNumRows;
}

int Matrix::getNumCols() const {
    return mNumCols;
}

// Indexing (1-based)
double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

const double& Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
            for (int i = 0; i < mNumRows; ++i) delete[] mData[i];
            delete[] mData;

            mNumRows = other.mNumRows;
            mNumCols = other.mNumCols;
            mData = new double*[mNumRows];
            for (int i = 0; i < mNumRows; ++i) {
                mData[i] = new double[mNumCols];
            }
        }
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                mData[i][j] = other.mData[i][j];
    }
    return *this;
}

// Unary operator
Matrix Matrix::operator+() const {
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = -mData[i][j];
    return result;
}

// Binary operators
Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}

Matrix operator*(double scalar, const Matrix& m) {
    return m * scalar;
}

// Determinant
double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2)
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];

    double det = 0.0;
    for (int p = 0; p < mNumCols; ++p) {
        Matrix minor(mNumRows - 1, mNumCols - 1);
        for (int i = 1; i < mNumRows; ++i) {
            int colIdx = 0;
            for (int j = 0; j < mNumCols; ++j) {
                if (j == p) continue;
                minor.mData[i - 1][colIdx] = mData[i][j];
                colIdx++;
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * mData[0][p] * minor.determinant();
    }
    return det;
}

// Inverse
Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix A(*this);
    Matrix I(n, n);
    for (int i = 0; i < n; ++i) I.mData[i][i] = 1.0;

    for (int i = 0; i < n; ++i) {
        double pivot = A.mData[i][i];
        assert(pivot != 0);
        for (int j = 0; j < n; ++j) {
            A.mData[i][j] /= pivot;
            I.mData[i][j] /= pivot;
        }
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = A.mData[k][i];
            for (int j = 0; j < n; ++j) {
                A.mData[k][j] -= factor * A.mData[i][j];
                I.mData[k][j] -= factor * I.mData[i][j];
            }
        }
    }
    return I;
}

// Pseudo inverse
Matrix Matrix::pseudoInverse() const {
    if (mNumRows >= mNumCols) {
        Matrix At(mNumCols, mNumRows);
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                At.mData[j][i] = mData[i][j];
        Matrix AtA = At * (*this);
        Matrix AtAinv = AtA.inverse();
        return AtAinv * At;
    } else {
        Matrix At(mNumCols, mNumRows);
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                At.mData[j][i] = mData[i][j];
        Matrix AAt = (*this) * At;
        Matrix AAtInv = AAt.inverse();
        return At * AAtInv;
    }
}

// cout << Matrix
std::ostream& operator<<(std::ostream& output, const Matrix& m) {
    for (int i = 0; i < m.mNumRows; ++i) {
        output << "[ ";
        for (int j = 0; j < m.mNumCols; ++j) {
            output << std::setw(8) << m.mData[i][j] << " ";
        }
        output << "]\n";
    }
    return output;
}

// Vector multi (Vector*Vector) 
Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.getSize());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mNumCols; ++j)
            sum += mData[i][j] * vec[j];
        result[i] = sum;
    }
    return result;
}

// // Code for testing
// int main() {
//     try {
//         std::cout << "--- Test Constructor ---" << std::endl;
//         Matrix A(2, 3);
//         std::cout << "Matrix A (2x3):\n" << A << std::endl;

//         std::cout << "--- Test Element Assignment ---" << std::endl;
//         A(1,1) = 1.0; A(1,2) = 2.0; A(1,3) = 3.0;
//         A(2,1) = 4.0; A(2,2) = 5.0; A(2,3) = 6.0;
//         std::cout << "Matrix A filled:\n" << A << std::endl;

//         std::cout << "--- Test Copy Constructor ---" << std::endl;
//         Matrix B = A;
//         std::cout << "Matrix B (copy of A):\n" << B << std::endl;

//         std::cout << "--- Test Assignment Operator ---" << std::endl;
//         Matrix C(2, 3);
//         C = A;
//         std::cout << "Matrix C (assigned from A):\n" << C << std::endl;

//         std::cout << "--- Test Addition ---" << std::endl;
//         Matrix D = A + B;
//         std::cout << "Matrix D = A + B:\n" << D << std::endl;

//         std::cout << "--- Test Subtraction ---" << std::endl;
//         Matrix E = D - A;
//         std::cout << "Matrix E = D - A (should be B):\n" << E << std::endl;

//         std::cout << "--- Test Scalar Multiplication ---" << std::endl;
//         Matrix F = A * 2.0;
//         std::cout << "Matrix F = A * 2:\n" << F << std::endl;

//         std::cout << "--- Test Matrix Multiplication ---" << std::endl;
//         Matrix G(3, 2);
//         G(1,1)=1; G(1,2)=2;
//         G(2,1)=3; G(2,2)=4;
//         G(3,1)=5; G(3,2)=6;
//         std::cout << "Matrix G (3x2):\n" << G << std::endl;

//         Matrix H = A * G;
//         std::cout << "Matrix H = A * G:\n" << H << std::endl;

//         std::cout << "--- Test Determinant (2x2) ---" << std::endl;
//         Matrix I(2,2);
//         I(1,1)=4; I(1,2)=7;
//         I(2,1)=2; I(2,2)=6;
//         std::cout << "Matrix I:\n" << I;
//         std::cout << "det(I) = " << I.determinant() << std::endl;

//         std::cout << "--- Test Inverse (2x2) ---" << std::endl;
//         Matrix I_inv = I.inverse();
//         std::cout << "I inverse:\n" << I_inv;

//         std::cout << "--- Test Pseudo-Inverse (3x2) ---" << std::endl;
//         Matrix Pseudo = G.pseudoInverse();
//         std::cout << "Pseudo-inverse of G:\n" << Pseudo << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }

//bash for test out matrix
//g++ -std=c++17 -Wall -g -IPartA/include PartA/source/vector.cpp PartA/source/matrix.cpp -o main
//./main