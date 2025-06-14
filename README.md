# Linear Algebra Library and CPU Performance Prediction

This project was developed as part of the **Programming 2** course at **Vietnamese-German University**. It demonstrates the development of a C++ linear algebra library and its application in predicting CPU performance using linear regression.

## Team Members

- **Pham Khac Uy** — 10423122  
- **Le Tri Dung** — 10423022  
- **Le Ngoc Khang Duy** — 10423024  
- **Supervisor:** Huynh Trung Hieu

## 📅 Date

**June 7, 2025**

---

## 📌 Overview

The project is divided into two main parts:

### Part A: Linear Algebra Library

Developed in C++, this library includes:

- `Vector` class
- `Matrix` class
- `LinearSystem` and derived `PosSymLinSystem` class
- Pseudo-inverse and Conjugate Gradient method support
- Handles under-/over-determined systems

### Part B: CPU Performance Prediction

Using the developed library, a linear regression model predicts CPU performance based on the UCI Machine Learning dataset. It involves:

- Data loading, shuffling, normalization
- Model training via Normal Equation with L2 regularization (Ridge Regression)
- Evaluation using RMSE

---

## 🏗️ Division of Work

### Le Tri Dung - 10423022

- Took charge of writing the main project report, including the introduction, methodology, experimental results, and conclusion.
- Organized and managed the project’s README, ensuring clear structure and comprehensive documentation.
- Designed the project folder structure for clarity and maintainability.
- Coordinated task allocation, managed version control, and ensured adherence to deadlines.
- Assisted in code review and integration for both Part A and Part B.

### Pham Khac Uy - 10423122

- Main responsibility for **Part B (CPU Performance Prediction)**.
- Implemented the data processing pipeline: data loading, shuffling, train/test split, and normalization.
- Developed the linear regression training, regularization, and evaluation modules.
- Conducted experiments, performance evaluation (RMSE), and result analysis.
- Contributed to and reviewed portions of Part A.

### Le Ngoc Khang Duy - 10423024

- Main responsibility for **Part A (Linear Algebra Library)**.
- Designed and implemented the core C++ classes: `Vector`, `Matrix`, `LinearSystem`, and `PosSymLinSystem`.
- Developed algorithms for matrix operations, including Gaussian Elimination, Conjugate Gradient, determinant, and pseudo-inverse.
- Wrote test cases, debugging support, and documentation for the library.
- Contributed to and reviewed portions of Part B.

---

## 🧠 Methodology

### Vector Class

- Arithmetic operations: addition, dot product, scalar multiplication
- Utility functions: magnitude, distance
- Indexing: supports both `[]` and `()`

### Matrix Class

- Supports matrix operations: addition, multiplication, inverse, determinant
- Memory management with deep copy and destructors
- Implements pseudo-inverse using Moore-Penrose

### LinearSystem Class

- Solves `Ax = b` using Gaussian Elimination with partial pivoting
- `PosSymLinSystem`: Uses Conjugate Gradient for symmetric positive definite matrices

### Special Cases

- Pseudo-inverse for non-square matrices
- Tikhonov Regularization (optional): `(AᵀA + λ²I)x = Aᵀb`

---

## 🧪 Data and Training

### Dataset

Used the UCI Machine Learning “Computer Hardware” dataset (209 instances) with:

- Features: `MYCT`, `MMIN`, `MMAX`, `CACH`, `CHMIN`, `CHMAX`
- Target: `PRP` (Published Relative Performance)

### Preprocessing

- Shuffled with Fisher-Yates algorithm
- Split: 80% training, 20% testing
- Min-max normalization on input features

### Training Method

Applied **Normal Equation** with L2 regularization:

```
θ = (XᵀX + λI)⁻¹XᵀY
```

Where `λ = 10.0`

### Evaluation Metric

- **Root Mean Squared Error (RMSE)** on both training and testing sets

---

## 📈 Results

| Metric           | Value     |
|------------------|-----------|
| **Train RMSE**   | 91.84     |
| **Test RMSE**    | 88.67     |

The slightly lower test RMSE suggests good generalization, possibly due to effective regularization.

---

## 📁 Project Structure

```
TINY-PROJECT/
├── PartA/
│   ├── include
│   │   ├── linear.h
│   │   ├── matrix.h
│   │   ├── possym.h
│   │   ├── vector.h
│   ├── source
│   │   ├── linear.cpp
│   │   ├── matrix.cpp
│   │   ├── possym.cpp
│   │   ├── vector.cpp
│   ├── main
│   ├── main.cpp
│   ├── Makefile
├── LinearRegressionPrediction
├── LinearRegressionPrediction.cpp
├── Makefile
├── README.md
├── machine.data
├── shuffled.txt
└── .vscode/
```

---

## 🔮 Future Work

- Improve linear algebra classes (error handling, QR factorization)
- Explore other solvers: LU decomposition, Jacobi, Gauss-Seidel
- Add other ML models: Lasso, polynomial regression, decision trees, SVM
- Optimize performance and memory usage

---

## 📂 Source Code

[🔗 GitHub Repository](https://github.com/mrsuero/Tiny-project)

---

## 📚 References

- UCI Machine Learning Repository: archive.ics.uci.edu
- Numerical Recipes in C++

---

## 👥 Contact

For questions or suggestions, feel free to contact the authors via GitHub.

---

## 📜 License

This project is for academic purposes under Vietnamese-German University coursework.