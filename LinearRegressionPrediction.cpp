#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>

#include "PartA/include/matrix.h"
#include "PartA/include/vector.h"

using namespace std;

// Print a matrix with a label
void printMatrix(const Matrix& m, const string& name) {
    cout << name << ":\n";
    for (int i = 1; i <= m.getNumRows(); i++) {
        for (int j = 1; j <= m.getNumCols(); j++) {
            cout << m(i, j) << " ";
        }
        cout << endl;
    }
}

// Randomly shuffle a list of lines (for data randomization)
void shuffleLines(vector<string>& lines) {
    random_device rd;
    mt19937 g(rd());
    shuffle(lines.begin(), lines.end(), g);
}

// Load selected columns (2 to 8) into input matrix
void loadInput(ifstream& datafile, Matrix& m) {
    string line;
    int rowIndex = 0;
    while (getline(datafile, line)) {
        if (rowIndex >= m.getNumRows()) break;
        stringstream ss(line);
        string value;
        int index = 0, colIndex = 0;
        while (getline(ss, value, ',')) {
            if (index >= 2 && index <= 8) {
                m(rowIndex + 1, colIndex + 1) = stod(value);
                colIndex++;
            }
            index++;
        }
        rowIndex++;
    }
}

// Load column 9 as output/target matrix
void loadOutput(ifstream& datafile, Matrix& m) {
    string line;
    int rowIndex = 0;
    while (getline(datafile, line)) {
        if (rowIndex >= m.getNumRows()) break;
        stringstream ss(line);
        string value;
        int index = 0;
        while (getline(ss, value, ',')) {
            if (index == 9) {
                m(rowIndex + 1, 1) = stod(value);
                break;
            }
            index++;
        }
        rowIndex++;
    }
}

// Compute mean and standard deviation for each column (feature)
void computeMeanStd(const Matrix& m, vector<double>& mean, vector<double>& std) {
    int rows = m.getNumRows();
    int cols = m.getNumCols();
    mean.resize(cols);
    std.resize(cols);
    for (int j = 1; j <= cols; j++) {
        double sum = 0.0, sqSum = 0.0;
        for (int i = 1; i <= rows; i++) {
            double val = m(i, j);
            sum += val;
            sqSum += val * val;
        }
        mean[j - 1] = sum / rows;
        double variance = (sqSum / rows) - mean[j - 1] * mean[j - 1];
        std[j - 1] = (variance > 1e-10) ? sqrt(variance) : 1.0; // Prevent division by zero
    }
}

// Normalize the matrix using the given mean and std
void normalizeMatrix(Matrix& m, const vector<double>& mean, const vector<double>& std) {
    int rows = m.getNumRows();
    int cols = m.getNumCols();
    for (int j = 1; j <= cols; j++) {
        for (int i = 1; i <= rows; i++) {
            m(i, j) = (m(i, j) - mean[j - 1]) / std[j - 1];
        }
    }
}

int main() {
    ifstream Dataset("machine.data");
    if (!Dataset.is_open()) {
        cerr << "Cannot open file machine.data" << endl;
        return 1;
    }

    // Read all lines from dataset for shuffling
    vector<string> lines;
    string line;
    while (getline(Dataset, line)) {
        lines.push_back(line);
    }
    Dataset.close();

    // Shuffle the dataset to avoid ordering bias
    shuffleLines(lines);

    // Save shuffled data to file
    ofstream outfile("shuffled.txt");
    if (!outfile.is_open()) {
        cerr << "Cannot open file shuffled.txt for writing" << endl;
        return 1;
    }
    for (const auto& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();

    // Split data into training and testing sets
    int total = lines.size();
    int trainSet = static_cast<int>(total * 0.8);
    int testSet = total - trainSet;

    cout << "Number of data(lines): " << total << endl;
    cout << "Training set size: " << trainSet << endl;
    cout << "Testing set size: " << testSet << endl;

    ifstream shuffled("shuffled.txt");
    if (!shuffled.is_open()) {
        cerr << "Cannot open file shuffled.txt for reading" << endl;
        return 1;
    }

    // Allocate matrices for input/output
    Matrix trainInput(trainSet, 7);
    Matrix trainTarget(trainSet, 1);
    Matrix testInput(testSet, 7);
    Matrix testTarget(testSet, 1);

    // Load training input matrix
    loadInput(shuffled, trainInput);

    // Rewind file stream to load training target
    shuffled.clear();
    shuffled.seekg(0);
    loadOutput(shuffled, trainTarget);

    // Skip training lines to load test input
    shuffled.clear();
    shuffled.seekg(0);
    string skip;
    for (int i = 0; i < trainSet; i++) getline(shuffled, skip);
    loadInput(shuffled, testInput);

    // Skip again to load test target
    shuffled.clear();
    shuffled.seekg(0);
    for (int i = 0; i < trainSet; i++) getline(shuffled, skip);
    loadOutput(shuffled, testTarget);
    shuffled.close();

    // Normalize input matrices using training set statistics
    vector<double> mean, stddev;
    computeMeanStd(trainInput, mean, stddev);
    normalizeMatrix(trainInput, mean, stddev);
    normalizeMatrix(testInput, mean, stddev);

    // Ridge Regression: theta = (X^T X + λI)^-1 X^T y
    Matrix Xt = trainInput.transpose();
    Matrix XtX = Xt * trainInput;
    double lambda = 10.0;

    // Add λ to the diagonal (ridge regularization)
    for (int i = 1; i <= XtX.getNumRows(); i++) {
        XtX(i, i) += lambda;
    }
    cout << "Applied regularization with lambda = " << lambda << endl;

    Matrix XtX_inv = XtX.pseudoInverse();
    Matrix Xty = Xt * trainTarget;
    Matrix theta = XtX_inv * Xty;

    // Predict on training set
    Matrix train_pred = trainInput * theta;
    double train_rmse = 0.0;
    for (int i = 1; i <= trainTarget.getNumRows(); i++) {
        double diff = trainTarget(i, 1) - train_pred(i, 1);
        train_rmse += diff * diff;
    }
    train_rmse = sqrt(train_rmse / trainTarget.getNumRows());

    // Predict on testing set
    Matrix test_pred = testInput * theta;
    double test_rmse = 0.0;
    for (int i = 1; i <= testTarget.getNumRows(); i++) {
        double diff = testTarget(i, 1) - test_pred(i, 1);
        test_rmse += diff * diff;
    }
    test_rmse = sqrt(test_rmse / testTarget.getNumRows());

    cout << "Train RMSE: " << train_rmse << endl;
    cout << "Test RMSE: " << test_rmse << endl;

    // Display learned linear model
    vector<string> featureNames = {"MYCT", "MMIN", "MMAX", "CACH", "CHMIN", "CHMAX", "VENDOR"};

    cout << "\nLinear Regression Model:" << endl;
    cout << "PRP = ";
    for (int i = 1; i <= theta.getNumRows(); i++) {
        double coef = theta(i, 1);
        if (i > 1) {
            cout << (coef >= 0 ? "+ " : "- ");
        }
        cout << abs(coef);
        if (i - 1 < featureNames.size()) {
            cout << " * " << featureNames[i - 1] << " ";
        }
    }
    cout << endl;

    return 0;
}