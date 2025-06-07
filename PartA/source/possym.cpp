#include "../include/possym.h"
PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    if (!IsSymmetric()) {
        throw std::invalid_argument("Matrix is not symmetric.");
    }
}

bool PosSymLinSystem::IsSymmetric() const {
    int n = mpA->getNumRows();
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if ((*mpA)(i, j) != (*mpA)(j, i)) return false;
        }
    }
    return true;
}

Vector PosSymLinSystem::Solve() const {
    int n = mpA->getNumRows();
    Vector x(n);
    Vector r = *mpb - (*mpA) * x;
    Vector p = r;
    Vector Ap(n);
    double rsold = r * r;

    for (int i = 0; i < n; ++i) {
        Ap = (*mpA) * p;
        double alpha = rsold / (p * Ap);
        x = x + alpha * p;
        r = r - alpha * Ap;
        double rsnew = r * r;
        if (std::sqrt(rsnew) < 1e-10) break;
        p = r + (rsnew / rsold) * p;
        rsold = rsnew;
    }

    return x;
}