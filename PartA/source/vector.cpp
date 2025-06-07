#include "../include/vector.h"
// #include <cassert>

// Accessor
int Vector::getSize() const { return mSize; }

// Constructors & Destructor
Vector::Vector() {
    mSize = 0;
    mData = nullptr;
}

Vector::Vector(int size) {
    if (size < 0)
        throw std::invalid_argument("Size must be non-negative");
    mSize = size;
    mData = new double[mSize];
}

Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

// Assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i)
            mData[i] = other.mData[i];
    }
    return *this;
}

// Unary operator
Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

Vector Vector::operator++() {
    for (int i = 0; i < mSize; ++i)
        ++mData[i];
    return *this;
}

Vector Vector::operator--() {
    for (int i = 0; i < mSize; ++i)
        --mData[i];
    return *this;
}

// Binary operators
Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Different size vectors!!");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Different size vectors!!");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
}

// Square bracket operator (0-based):
double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of bounds (0-based)");
    return mData[index];
}

const double& Vector::operator[](int index) const {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of bounds (0-based)");
    return mData[index];
}

// Round bracket operator (1-based):
double& Vector::operator()(int index) {
    if (index <= 0 || index > mSize)
        throw std::out_of_range("Index out of bounds (1-based)");
    return mData[index - 1];
}

const double& Vector::operator()(int index) const {
    if (index <= 0 || index > mSize)
        throw std::out_of_range("Index out of bounds (1-based)");
    return mData[index - 1];
}

// Dot product
double Vector::operator*(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Vectors must be of the same size for dot product");
    double result = 0.0;
    for (int i = 0; i < mSize; ++i)
        result += mData[i] * other.mData[i];
    return result;
}

// // Code for testing each function.
// int main() {
//     try {
//         std::cout << "===== TEST CONSTRUCTOR =====" << std::endl;
//         Vector v1(3); // v1 = [0, 0, 0]
//         v1[0] = 1.0;
//         v1[1] = 2.0;
//         v1[2] = 3.0;

//         std::cout << "v1 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << v1[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "\n===== TEST COPY CONSTRUCTOR =====" << std::endl;
//         Vector v2 = v1;
//         std::cout << "v2 (copy of v1) = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << v2[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "\n===== TEST ASSIGNMENT OPERATOR =====" << std::endl;
//         Vector v3;
//         v3 = v1;
//         std::cout << "v3 (assigned from v1) = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << v3[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "\n===== TEST UNARY OPERATORS =====" << std::endl;
//         Vector vNeg = -v1;
//         std::cout << "-v1 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << vNeg[i] << " ";
//         std::cout << "]" << std::endl;

//         ++v1;
//         std::cout << "++v1 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << v1[i] << " ";
//         std::cout << "]" << std::endl;

//         --v1;
//         std::cout << "--v1 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << v1[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "\n===== TEST BINARY OPERATORS =====" << std::endl;
//         Vector v4(3);
//         v4[0] = 5.0; v4[1] = 4.0; v4[2] = 3.0;

//         Vector sum = v1 + v4;
//         Vector diff = v1 - v4;
//         Vector scaled1 = v1 * 2.0;
//         Vector scaled2 = 3.0 * v1;

//         std::cout << "v1 + v4 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << sum[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "v1 - v4 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << diff[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "v1 * 2 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << scaled1[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "3 * v1 = [ ";
//         for (int i = 0; i < 3; ++i) std::cout << scaled2[i] << " ";
//         std::cout << "]" << std::endl;

//         std::cout << "\n===== TEST INDEXING [] (0-based) =====" << std::endl;
//         std::cout << "v1[0] = " << v1[0] << ", v1[2] = " << v1[2] << std::endl;

//         std::cout << "\n===== TEST INDEXING () (1-based) =====" << std::endl;
//         std::cout << "v1(1) = " << v1(1) << ", v1(3) = " << v1(3) << std::endl;

//         std::cout << "\n===== TEST OUT OF RANGE =====" << std::endl;
//         try {
//             std::cout << v1[100] << std::endl;
//         } catch (std::exception& e) {
//             std::cout << "Caught exception for v1[100]: " << e.what() << std::endl;
//         }

//         try {
//             std::cout << v1(0) << std::endl;
//         } catch (std::exception& e) {
//             std::cout << "Caught exception for v1(0): " << e.what() << std::endl;
//         }

//         std::cout << "\n===== ALL TESTS PASSED SUCCESSFULLY =====" << std::endl;

//     } catch (std::exception& e) {
//         std::cerr << "Unexpected exception: " << e.what() << std::endl;
//     }

//     return 0;
// }