#include "DenseMatrix.h"
#include <iostream>

DenseMatrix::DenseMatrix(int r, int c) : rows(r), cols(c) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols]();
    }
}

DenseMatrix::DenseMatrix(const DenseMatrix& other) : rows(other.rows), cols(other.cols) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

DenseMatrix::~DenseMatrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

DenseMatrix& DenseMatrix::operator=(const DenseMatrix& other) {
    if (this == &other) return *this;

    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;

    rows = other.rows;
    cols = other.cols;
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

void DenseMatrix::setValue(int r, int c, double val) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        data[r][c] = val;
    }
}

double DenseMatrix::getValue(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return data[r][c];
    }
    return 0.0;
}

DenseMatrix DenseMatrix::operator+(const DenseMatrix& other) const {
    DenseMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

DenseMatrix DenseMatrix::operator-(const DenseMatrix& other) const {
    DenseMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& other) const {
    DenseMatrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

DenseMatrix DenseMatrix::operator/(const DenseMatrix& other) const {
    DenseMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (other.data[i][j] != 0) {
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
    }
    return result;
}

DenseMatrix DenseMatrix::transpose() const {
    DenseMatrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

void DenseMatrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
