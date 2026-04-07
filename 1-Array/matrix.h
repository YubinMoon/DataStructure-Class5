#ifndef MATRIX_H
#define MATRIX_H

struct Element {
    int row;
    int col;
    double data; 
};

class Matrix {
private:
    Element* elements;

public:
    Matrix(int max_terms);
    ~Matrix();

    void addElement(int r, int c, double val);

    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator/(const Matrix& other);
};

#endif