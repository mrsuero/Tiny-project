#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cassert>
#include <iomanip>
#include "../include/vector.h" // for Vector*Vector -> linear can work

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructor & Destructor
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    // Accessors
    int getNumRows() const;
    int getNumCols() const;

    // Indexing (1-based)
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    // Unary operator
    Matrix operator+() const;
    Matrix operator-() const;

    // Binary operators
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const; // matrix * matrix
    Matrix operator*(double scalar) const;       // matrix * scalar
    friend Matrix operator*(double scalar, const Matrix& m); // scalar * matrix

    // Determinant
    double determinant() const;

    // Inverse
    Matrix inverse() const;

    // Pseudo inverse
    Matrix pseudoInverse() const;

    // cout << Matrix
    friend std::ostream& operator<<(std::ostream& output, const Matrix& m);

    // Vector multi (Vectox*Vector) (for linear to work)
    Vector operator*(const Vector& vec) const;

};

#endif