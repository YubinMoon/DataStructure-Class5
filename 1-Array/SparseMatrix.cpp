#include "SparseMatrix.h"
#include <iostream>
#include <algorithm>

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
    int terms = (int)other.elements[0].data;
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
    int terms = (int)other.elements[0].data;
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
    int terms = (int)elements[0].data;
    if (terms + 1 >= capacity)
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
    elements[0].data = (double)terms;
}

static bool compareElements(const Element &a, const Element &b)
{
    if (a.row != b.row)
        return a.row < b.row;
    return a.col < b.col;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int aTerms = (int)elements[0].data;
    int bTerms = (int)other.elements[0].data;

    SparseMatrix result(rows, cols, aTerms + bTerms + 1);
    int i = 1, j = 1;
    while (i <= aTerms && j <= bTerms)
    {
        int aIdx = elements[i].row * cols + elements[i].col;
        int bIdx = other.elements[j].row * cols + other.elements[j].col;

        if (aIdx < bIdx)
        {
            result.addElement(elements[i].row, elements[i].col, elements[i].data);
            i++;
        }
        else if (aIdx > bIdx)
        {
            result.addElement(other.elements[j].row, other.elements[j].col, other.elements[j].data);
            j++;
        }
        else
        {
            double sum = elements[i].data + other.elements[j].data;
            if (sum != 0.0)
                result.addElement(elements[i].row, elements[i].col, sum);
            i++;
            j++;
        }
    }
    for (; i <= aTerms; i++)
        result.addElement(elements[i].row, elements[i].col, elements[i].data);
    for (; j <= bTerms; j++)
        result.addElement(other.elements[j].row, other.elements[j].col, other.elements[j].data);

    int resTerms = (int)result.elements[0].data;
    if (resTerms > 0)
        std::sort(result.elements + 1, result.elements + resTerms + 1, compareElements);
    return result;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int aTerms = (int)elements[0].data;
    int bTerms = (int)other.elements[0].data;

    SparseMatrix result(rows, cols, aTerms + bTerms + 1);
    int i = 1, j = 1;
    while (i <= aTerms && j <= bTerms)
    {
        int aIdx = elements[i].row * cols + elements[i].col;
        int bIdx = other.elements[j].row * cols + other.elements[j].col;

        if (aIdx < bIdx)
        {
            result.addElement(elements[i].row, elements[i].col, elements[i].data);
            i++;
        }
        else if (aIdx > bIdx)
        {
            result.addElement(other.elements[j].row, other.elements[j].col, -other.elements[j].data);
            j++;
        }
        else
        {
            double diff = elements[i].data - other.elements[j].data;
            if (diff != 0.0)
                result.addElement(elements[i].row, elements[i].col, diff);
            i++;
            j++;
        }
    }
    for (; i <= aTerms; i++)
        result.addElement(elements[i].row, elements[i].col, elements[i].data);
    for (; j <= bTerms; j++)
        result.addElement(other.elements[j].row, other.elements[j].col, -other.elements[j].data);

    int resTerms = (int)result.elements[0].data;
    if (resTerms > 0)
        std::sort(result.elements + 1, result.elements + resTerms + 1, compareElements);
    return result;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int other_cols = (int)other.elements[0].col;
    int aTerms = (int)elements[0].data;

    SparseMatrix result(rows, other_cols);
    SparseMatrix bTrans = other.transpose();
    int bTerms = (int)bTrans.elements[0].data;

    int i = 1;
    while (i <= aTerms)
    {
        int r = elements[i].row;
        int rStart = i;
        while (i <= aTerms && elements[i].row == r)
            i++;
        int rEnd = i;

        int j = 1;
        while (j <= bTerms)
        {
            int c = bTrans.elements[j].row;
            int cStart = j;
            while (j <= bTerms && bTrans.elements[j].row == c)
                j++;
            int cEnd = j;

            double sum = 0.0;
            int pA = rStart, pB = cStart;
            while (pA < rEnd && pB < cEnd)
            {
                if (elements[pA].col < bTrans.elements[pB].col)
                    pA++;
                else if (elements[pA].col > bTrans.elements[pB].col)
                    pB++;
                else
                {
                    sum += elements[pA].data * bTrans.elements[pB].data;
                    pA++;
                    pB++;
                }
            }
            if (sum != 0.0)
                result.addElement(r, c, sum);
        }
    }
    int resTerms = (int)result.elements[0].data;
    if (resTerms > 0)
        std::sort(result.elements + 1, result.elements + resTerms + 1, compareElements);
    return result;
}

SparseMatrix SparseMatrix::operator/(const SparseMatrix &other) const
{
    int rows = elements[0].row;
    int cols = elements[0].col;
    int aTerms = (int)elements[0].data;
    int bTerms = (int)other.elements[0].data;

    SparseMatrix result(rows, cols);
    int i = 1, j = 1;
    while (i <= aTerms && j <= bTerms)
    {
        int aIdx = elements[i].row * cols + elements[i].col;
        int bIdx = other.elements[j].row * cols + other.elements[j].col;

        if (aIdx < bIdx)
        {
            i++;
        }
        else if (aIdx > bIdx)
        {
            j++;
        }
        else
        {
            if (other.elements[j].data != 0.0)
            {
                double val = elements[i].data / other.elements[j].data;
                if (val != 0.0)
                    result.addElement(elements[i].row, elements[i].col, val);
            }
            i++;
            j++;
        }
    }
    int resTerms = (int)result.elements[0].data;
    if (resTerms > 0)
        std::sort(result.elements + 1, result.elements + resTerms + 1, compareElements);
    return result;
}

SparseMatrix SparseMatrix::transpose() const
{
    SparseMatrix result(elements[0].col, elements[0].row);
    int terms = (int)elements[0].data;
    for (int i = 1; i <= terms; i++)
    {
        result.addElement(elements[i].col, elements[i].row, elements[i].data);
    }
    int resTerms = (int)result.elements[0].data;
    if (resTerms > 0)
        std::sort(result.elements + 1, result.elements + resTerms + 1, compareElements);
    return result;
}

void SparseMatrix::print() const
{
    int terms = (int)elements[0].data;
    for (int i = 1; i <= terms; ++i)
    {
        std::cout << "[" << elements[i].row << "][" << elements[i].col << "] = " << elements[i].data << "\n";
    }
}

double SparseMatrix::getValue(int r, int c) const
{
    int terms = (int)elements[0].data;
    for (int i = 1; i <= terms; ++i)
    {
        if (elements[i].row == r && elements[i].col == c)
            return elements[i].data;
    }
    return 0.0;
}
