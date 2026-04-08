#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(int r, int c, int cap) : capacity(cap)
{
    if (capacity < 1)
        capacity = 10;
    elements = new Element[capacity];
    elements[0].row = r;
    elements[0].col = c;
    elements[0].data = 0;
}

SparseMatrix::SparseMatrix(const SparseMatrix &other) : capacity(other.capacity)
{
    elements = new Element[capacity];
    int terms = other.elements[0].data;
    for (int i = 0; i <= terms; ++i)
    {
        elements[i] = other.elements[i];
    }
}

SparseMatrix::~SparseMatrix()
{
    delete[] elements;
}

SparseMatrix &SparseMatrix::operator=(const SparseMatrix &other)
{
    if (this == &other)
        return *this;
    delete[] elements;
    capacity = other.capacity;
    elements = new Element[capacity];
    int terms = other.elements[0].data;
    for (int i = 0; i <= terms; ++i)
    {
        elements[i] = other.elements[i];
    }
    return *this;
}

void SparseMatrix::addElement(int r, int c, double val)
{
    if (val == 0.0)
        return;
    int terms = elements[0].data;
    if (terms + 1 == capacity)
    {
        capacity *= 2;
        Element *newElements = new Element[capacity];
        for (int i = 0; i <= terms; ++i)
        {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }
    terms++;
    elements[terms].row = r;
    elements[terms].col = c;
    elements[terms].data = val;
    elements[0].data = terms;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int terms = elements[0].data;
    int other_terms = other.elements[0].data;

    SparseMatrix result(rows, cols, terms + other_terms + 1);
    int aPos = 1, bPos = 1;
    while (aPos <= terms && bPos <= other_terms)
    {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.elements[0].col + other.elements[bPos].col;

        if (aIdx < bIdx)
        {
            result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
            aPos++;
        }
        else if (aIdx > bIdx)
        {
            result.addElement(other.elements[bPos].row, other.elements[bPos].col, other.elements[bPos].data);
            bPos++;
        }
        else
        {
            double sum = elements[aPos].data + other.elements[bPos].data;
            if (sum != 0.0)
            {
                result.addElement(elements[aPos].row, elements[aPos].col, sum);
            }
            aPos++;
            bPos++;
        }
    }
    for (; aPos <= terms; aPos++)
        result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
    for (; bPos <= other_terms; bPos++)
        result.addElement(other.elements[bPos].row, other.elements[bPos].col, other.elements[bPos].data);
    return result;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int terms = elements[0].data;
    int other_terms = other.elements[0].data;

    SparseMatrix result(rows, cols, terms + other_terms + 1);
    int aPos = 1, bPos = 1;
    while (aPos <= terms && bPos <= other_terms)
    {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.elements[0].col + other.elements[bPos].col;

        if (aIdx < bIdx)
        {
            result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
            aPos++;
        }
        else if (aIdx > bIdx)
        {
            result.addElement(other.elements[bPos].row, other.elements[bPos].col, -other.elements[bPos].data);
            bPos++;
        }
        else
        {
            double diff = elements[aPos].data - other.elements[bPos].data;
            if (diff != 0.0)
            {
                result.addElement(elements[aPos].row, elements[aPos].col, diff);
            }
            aPos++;
            bPos++;
        }
    }
    for (; aPos <= terms; aPos++)
        result.addElement(elements[aPos].row, elements[aPos].col, elements[aPos].data);
    for (; bPos <= other_terms; bPos++)
        result.addElement(other.elements[bPos].row, other.elements[bPos].col, -other.elements[bPos].data);
    return result;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int other_cols = other.elements[0].col;
    int terms = elements[0].data;

    SparseMatrix result(rows, other_cols);
    SparseMatrix bTrans = other.transpose();
    int bTrans_terms = bTrans.elements[0].data;

    for (int i = 1; i <= terms;)
    {
        int r = elements[i].row;
        int rEnd = i;
        while (rEnd <= terms && elements[rEnd].row == r)
            rEnd++;

        for (int j = 1; j <= bTrans_terms;)
        {
            int c = bTrans.elements[j].row;
            int cEnd = j;
            while (cEnd <= bTrans_terms && bTrans.elements[cEnd].row == c)
                cEnd++;

            double sum = 0.0;
            int aPos = i, bPos = j;
            while (aPos < rEnd && bPos < cEnd)
            {
                if (elements[aPos].col < bTrans.elements[bPos].col)
                    aPos++;
                else if (elements[aPos].col > bTrans.elements[bPos].col)
                    bPos++;
                else
                {
                    sum += elements[aPos].data * bTrans.elements[bPos].data;
                    aPos++;
                    bPos++;
                }
            }
            if (sum != 0.0)
                result.addElement(r, c, sum);
            j = cEnd;
        }
        i = rEnd;
    }
    return result;
}

SparseMatrix SparseMatrix::operator/(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int terms = elements[0].data;
    int other_terms = other.elements[0].data;

    SparseMatrix result(rows, cols, terms + 1);
    int aPos = 1, bPos = 1;
    while (aPos <= terms && bPos <= other_terms)
    {
        int aIdx = elements[aPos].row * cols + elements[aPos].col;
        int bIdx = other.elements[bPos].row * other.elements[0].col + other.elements[bPos].col;

        if (aIdx < bIdx)
        {
            aPos++;
        }
        else if (aIdx > bIdx)
        {
            bPos++;
        }
        else
        {
            if (other.elements[bPos].data != 0.0)
            {
                double div = elements[aPos].data / other.elements[bPos].data;
                if (div != 0.0)
                {
                    result.addElement(elements[aPos].row, elements[aPos].col, div);
                }
            }
            aPos++;
            bPos++;
        }
    }
    return result;
}

SparseMatrix SparseMatrix::transpose() const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int terms = elements[0].data;

    SparseMatrix result(cols, rows, terms + 1);
    result.elements[0].data = terms;

    if (terms > 0)
    {
        int *rowTerms = new int[cols]();
        int *startingPos = new int[cols]();

        for (int i = 1; i <= terms; i++)
            rowTerms[elements[i].col]++;
        startingPos[0] = 1;
        for (int i = 1; i < cols; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

        for (int i = 1; i <= terms; i++)
        {
            int j = startingPos[elements[i].col]++;
            result.elements[j].row = elements[i].col;
            result.elements[j].col = elements[i].row;
            result.elements[j].data = elements[i].data;
        }
        delete[] rowTerms;
        delete[] startingPos;
    }
    return result;
}

void SparseMatrix::print() const
{
    int terms = elements[0].data;
    for (int i = 1; i <= terms; ++i)
    {
        std::cout << "[" << elements[i].row << "][" << elements[i].col << "] = " << elements[i].data << "\n";
    }
}
