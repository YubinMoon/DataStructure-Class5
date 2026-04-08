#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(int r, int c, int cap) : rows(r), cols(c), terms(0), capacity(cap) {
    elements = new Element[capacity];
}

SparseMatrix::SparseMatrix(const SparseMatrix& other) : rows(other.rows), cols(other.cols), terms(other.terms), capacity(other.capacity) {
    elements = new Element[capacity];
    for (int i = 0; i < terms; ++i) {
        elements[i] = other.elements[i];
    }
}

SparseMatrix::~SparseMatrix() {
    delete[] elements;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& other) {
    if (this == &other) return *this;
    delete[] elements;
    rows = other.rows;
    cols = other.cols;
    terms = other.terms;
    capacity = other.capacity;
    elements = new Element[capacity];
    for (int i = 0; i < terms; ++i) {
        elements[i] = other.elements[i];
    }
    return *this;
}

void SparseMatrix::addElement(int r, int c, double val) {
    if (val == 0.0) return;
    if (terms == capacity) {
        capacity *= 2;
        Element* newElements = new Element[capacity];
        for (int i = 0; i < terms; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }
    elements[terms].row = r;
    elements[terms].col = c;
    elements[terms].data = val;
    terms++;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& other) const {
    SparseMatrix result(rows, cols, terms + other.terms);
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < other.terms) {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.cols + other.elements[bPos].col;

        if (aIdx < bIdx) {
            result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
            aPos++;
        } else if (aIdx > bIdx) {
            result.addElement(other.elements[bPos].row, other.elements[bPos].col, other.elements[bPos].data);
            bPos++;
        } else {
            double sum = elements[aPos].data + other.elements[bPos].data;
            if (sum != 0.0) {
                result.addElement(elements[aPos].row, elements[aPos].col, sum);
            }
            aPos++;
            bPos++;
        }
    }
    for (; aPos < terms; aPos++) result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
    for (; bPos < other.terms; bPos++) result.addElement(other.elements[bPos].row, other.elements[bPos].col, other.elements[bPos].data);
    return result;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix& other) const {
    SparseMatrix result(rows, cols, terms + other.terms);
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < other.terms) {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.cols + other.elements[bPos].col;

        if (aIdx < bIdx) {
            result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
            aPos++;
        } else if (aIdx > bIdx) {
            result.addElement(other.elements[bPos].row, other.elements[bPos].col, -other.elements[bPos].data);
            bPos++;
        } else {
            double diff = elements[aPos].data - other.elements[bPos].data;
            if (diff != 0.0) {
                result.addElement(elements[aPos].row, elements[aPos].col, diff);
            }
            aPos++;
            bPos++;
        }
    }
    for (; aPos < terms; aPos++) result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
    for (; bPos < other.terms; bPos++) result.addElement(other.elements[bPos].row, other.elements[bPos].col, -other.elements[bPos].data);
    return result;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& other) const {
    SparseMatrix result(rows, other.cols);
    SparseMatrix bTrans = other.transpose();

    for (int i = 0; i < terms; ) {
        int r = elements[i].row;
        int rEnd = i;
        while (rEnd < terms && elements[rEnd].row == r) rEnd++;

        for (int j = 0; j < bTrans.terms; ) {
            int c = bTrans.elements[j].row;
            int cEnd = j;
            while (cEnd < bTrans.terms && bTrans.elements[cEnd].row == c) cEnd++;

            double sum = 0.0;
            int aPos = i, bPos = j;
            while (aPos < rEnd && bPos < cEnd) {
                if (elements[aPos].col < bTrans.elements[bPos].col) aPos++;
                else if (elements[aPos].col > bTrans.elements[bPos].col) bPos++;
                else {
                    sum += elements[aPos].data * bTrans.elements[bPos].data;
                    aPos++;
                    bPos++;
                }
            }
            if (sum != 0.0) result.addElement(r, c, sum);
            j = cEnd;
        }
        i = rEnd;
    }
    return result;
}

SparseMatrix SparseMatrix::operator/(const SparseMatrix& other) const {
    SparseMatrix result(rows, cols, terms);
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < other.terms) {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.cols + other.elements[bPos].col;

        if (aIdx < bIdx) {
            aPos++;
        } else if (aIdx > bIdx) {
            bPos++;
        } else {
            if (other.elements[bPos].data != 0.0) {
                double div = elements[aPos].data / other.elements[bPos].data;
                if (div != 0.0) {
                    result.addElement(elements[aPos].row, elements[aPos].col, div);
                }
            }
            aPos++;
            bPos++;
        }
    }
    return result;
}

SparseMatrix SparseMatrix::transpose() const {
    SparseMatrix result(cols, rows, terms);
    if (terms > 0) {
        int* rowTerms = new int[cols]();
        int* startingPos = new int[cols]();

        for (int i = 0; i < terms; i++) rowTerms[elements[i].col]++;
        startingPos[0] = 0;
        for (int i = 1; i < cols; i++) startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

        for (int i = 0; i < terms; i++) {
            int j = startingPos[elements[i].col]++;
            result.elements[j].row = elements[i].col;
            result.elements[j].col = elements[i].row;
            result.elements[j].data = elements[i].data;
        }
        result.terms = terms;
        delete[] rowTerms;
        delete[] startingPos;
    }
    return result;
}

void SparseMatrix::print() const {
    for (int i = 0; i < terms; ++i) {
        std::cout << "[" << elements[i].row << "][" << elements[i].col << "] = " << elements[i].data << "\n";
    }
}
