#include "../include/linear.h"
#include <cassert>
#include <iostream>

// Constructor
LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    if (A.getNumRows() != A.getNumCols()) throw std::invalid_argument("Matrix must be square.");
    if (A.getNumRows() != b.getSize()) throw std::invalid_argument("Matrix and vector size mismatch.");
    mSize = A.getNumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

// Destructor
LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

// Gaussian Elimination with partial pivoting
Vector LinearSystem::Solve() const {
    Matrix A(*mpA);
    Vector b(*mpb);
    Vector x(mSize);

    for (int i = 0; i < mSize; ++i) {
        // Partial Pivoting
        int maxRow = i;
        for (int k = i + 1; k < mSize; ++k) {
            if (std::abs(A(k+1, i+1)) > std::abs(A(maxRow+1, i+1))) {
                maxRow = k;
            }
        }
        for (int j = 1; j <= mSize; ++j) std::swap(A(i+1, j), A(maxRow+1, j));
        std::swap(b[i], b[maxRow]);

        // Elimination
        for (int k = i + 1; k < mSize; ++k) {
            double factor = A(k+1, i+1) / A(i+1, i+1);
            for (int j = i; j < mSize; ++j) A(k+1, j+1) -= factor * A(i+1, j+1);
            b[k] -= factor * b[i];
        }
    }

    // Back substitution
    for (int i = mSize - 1; i >= 0; --i) {
        double sum = b[i];
        for (int j = i + 1; j < mSize; ++j) sum -= A(i+1, j+1) * x[j];
        x[i] = sum / A(i+1, i+1);
    }
    return x;
}