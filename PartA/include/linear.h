#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "matrix.h"
#include "vector.h"
#include <stdexcept>
#include <cmath>

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();

    // Gaussian Elimination with partial pivoting
    virtual Vector Solve() const; 

private:
    // prevent copy
    LinearSystem(const LinearSystem&);
};

#endif
