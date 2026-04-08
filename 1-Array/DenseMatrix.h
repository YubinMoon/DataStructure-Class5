#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

class DenseMatrix {
private:
    int rows;
    int cols;
    double** data;

public:
    DenseMatrix(int r, int c);
    DenseMatrix(const DenseMatrix& other);
    ~DenseMatrix();

    DenseMatrix& operator=(const DenseMatrix& other);

    void setValue(int r, int c, double val);
    double getValue(int r, int c) const;

    DenseMatrix operator+(const DenseMatrix& other) const;
    DenseMatrix operator-(const DenseMatrix& other) const;
    DenseMatrix operator*(const DenseMatrix& other) const;
    DenseMatrix operator/(const DenseMatrix& other) const;

    DenseMatrix transpose() const;
    void print() const;
};

#endif
