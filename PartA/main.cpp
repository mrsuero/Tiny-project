// main_test_all.cpp
#include <iostream>
#include "../PartA/include/vector.h"
#include "../PartA/include/matrix.h"
#include "../PartA/include/linear.h"
#include "../PartA/include/possym.h"

void TestVector() {
    std::cout << "Testing Vector operations:\n";
    Vector v1(3);
    v1(1) = 1.0; v1(2) = 2.0; v1(3) = 3.0;

    Vector v2 = v1;
    Vector v3 = v1 + v2;
    Vector v4 = v1 * 2.0;

    for (int i = 0; i < v3.getSize(); ++i) {
        std::cout << "v3(" << i+1 << ") = " << v3(i+1) << ", v4(" << i+1 << ") = " << v4(i+1) << "\n";
    }
    std::cout << "Dot product: " << v1 * v2 << "\n\n";
}

void TestMatrix() {
    std::cout << "Testing Matrix operations:\n";
    Matrix A(2,2);
    A(1,1) = 1; A(1,2) = 2;
    A(2,1) = 3; A(2,2) = 4;

    Matrix B = A;
    Matrix C = A + B;
    Matrix D = A * 2.0;

    std::cout << "C(1,1) = " << C(1,1) << ", D(2,2) = " << D(2,2) << "\n";
    std::cout << "Determinant: " << A.determinant() << "\n";
    std::cout << "Inverse: \n" << A.inverse() << "\n";

    Matrix E(2,3);
    E(1,1)=1; E(1,2)=2; E(1,3)=3;
    E(2,1)=4; E(2,2)=5; E(2,3)=6;
    std::cout << "Pseudo-inverse of 2x3 matrix:\n" << E.pseudoInverse() << "\n\n";
}

void TestGaussianElimination() {
    std::cout << "Testing LinearSystem (Gaussian Elimination):\n";
    Matrix A(3,3);
    A(1,1)=2; A(1,2)=-1; A(1,3)=0;
    A(2,1)=-1; A(2,2)=2; A(2,3)=-1;
    A(3,1)=0; A(3,2)=-1; A(3,3)=2;

    Vector b(3);
    b(1)=1; b(2)=0; b(3)=1;

    LinearSystem sys(A, b);
    Vector x = sys.Solve();

    for (int i = 0; i < x.getSize(); ++i) {
        std::cout << "x(" << i+1 << ") = " << x(i+1) << "\n";
    }
    std::cout << "\n";
}

void TestConjugateGradient() {
    std::cout << "Testing PosSymLinSystem (Conjugate Gradient):\n";
    Matrix A(3,3);
    A(1,1)=4; A(1,2)=1; A(1,3)=2;
    A(2,1)=1; A(2,2)=3; A(2,3)=0;
    A(3,1)=2; A(3,2)=0; A(3,3)=1;

    Vector b(3);
    b(1)=4; b(2)=5; b(3)=6;

    PosSymLinSystem sys(A, b);
    Vector x = sys.Solve();

    for (int i = 0; i < x.getSize(); ++i) {
        std::cout << "x(" << i+1 << ") = " << x(i+1) << "\n";
    }
    std::cout << "\n";
}

void TestNonSquareSystem() {
    std::cout << "Testing over-determined system with pseudo-inverse:\n";
    Matrix A(4, 2);
    A(1,1) = 1; A(1,2) = 1;
    A(2,1) = 1; A(2,2) = 2;
    A(3,1) = 1; A(3,2) = 3;
    A(4,1) = 1; A(4,2) = 4;

    Vector b(4);
    b(1) = 6; b(2) = 5; b(3) = 7; b(4) = 10;

    Matrix A_pinv = A.pseudoInverse();
    Vector x = A_pinv * b;

    std::cout << "Estimated solution (least-squares):\n";
    for (int i = 0; i < x.getSize(); ++i) {
        std::cout << "x(" << i+1 << ") = " << x(i+1) << "\n";
    }
    std::cout << "\n";
}

int main() {
    TestVector();
    TestMatrix();
    TestGaussianElimination();
    TestConjugateGradient();
    TestNonSquareSystem();
    return 0;
}
