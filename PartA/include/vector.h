#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

class Vector{
    private:
    int mSize;
    double *mData;

    public:
    // Accessor
    int getSize() const;

    // Constructor & Destructor
    Vector();
    Vector(int _mSize);
    ~Vector();
    Vector(const Vector& otherVector); 

    // Assignment operator
    Vector& operator=(const Vector& otherVector);

    // Unary operator
    Vector operator-() const;
    Vector operator+() const;
    Vector operator++();
    Vector operator--();

    // Binary operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;                      // vector x scalar
    friend Vector operator*(double scalar, const Vector& v);    // scalar x vector

    // Square bracket operator (0-based):
    double& operator[](int index);
    const double& operator[](int index) const;

    // Round bracket operator (1-based):
    double& operator()(int index);
    const double& operator()(int index) const;

    // cout << Vector
    // friend std::ostream& operator<<(std::ostream& out, const Vector& v);

    // Dot product (for linear to work)
    double operator*(const Vector& other) const;


    
};

#endif // VECTOR_H
