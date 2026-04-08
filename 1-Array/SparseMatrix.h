#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <algorithm>

struct Element
{
    int row;
    int col;
    double data;
};

class SparseMatrix
{
private:
    int capacity;
    Element *elements;

    void quickSort(int low, int high);

public:
    SparseMatrix(int r, int c, int cap = 10);
    SparseMatrix(const SparseMatrix &other);
    ~SparseMatrix();

    SparseMatrix &operator=(const SparseMatrix &other);

    void addElement(int r, int c, double val);

    SparseMatrix operator+(const SparseMatrix &other) const;
    SparseMatrix operator-(const SparseMatrix &other) const;
    SparseMatrix operator*(const SparseMatrix &other) const;
    SparseMatrix operator/(const SparseMatrix &other) const;

    SparseMatrix transpose() const;
    void print() const;
    double getValue(int r, int c) const;
};

#endif
