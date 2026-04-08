#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool are_equal(double a, double b)
{
    if (isnan(a) && isnan(b))
        return true;
    return abs(a - b) < 1e-6;
}

DenseMatrix read_dense(string filename)
{
    ifstream file("test_data/" + filename + ".txt");
    if (!file.is_open())
    {
        cerr << "Failed to open test_data/" << filename << ".txt" << endl;
        exit(1);
    }
    int r, c;
    file >> r >> c;
    DenseMatrix mat(r, c);
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            double val;
            file >> val;
            mat.setValue(i, j, val);
        }
    }
    return mat;
}

SparseMatrix read_sparse(string filename)
{
    ifstream file("test_data/" + filename + ".txt");
    if (!file.is_open())
    {
        cerr << "Failed to open test_data/" << filename << ".txt" << endl;
        exit(1);
    }
    int r, c;
    file >> r >> c;
    SparseMatrix mat(r, c);
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            double val;
            file >> val;
            if (val != 0.0)
                mat.addElement(i, j, val);
        }
    }
    return mat;
}

bool verify(const DenseMatrix &d, const SparseMatrix &s, string expected_file)
{
    ifstream file("test_data/" + expected_file + ".txt");
    if (!file.is_open())
    {
        cerr << "Failed to open test_data/" << expected_file << ".txt" << endl;
        exit(1);
    }
    int r, c;
    file >> r >> c;
    bool ok = true;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            double exp;
            file >> exp;
            double d_val = d.getValue(i, j);
            double s_val = s.getValue(i, j);

            if (!are_equal(d_val, exp))
            {
                cout << "  [Dense Error] at [" << i << "][" << j << "]: expected " << exp << ", got " << d_val << endl;
                ok = false;
            }
            if (!are_equal(s_val, exp))
            {
                cout << "  [Sparse Error] at [" << i << "][" << j << "]: expected " << exp << ", got " << s_val << endl;
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    DenseMatrix dA = read_dense("input_a");
    DenseMatrix dB = read_dense("input_b");
    DenseMatrix dC = read_dense("input_c");
    DenseMatrix dD = read_dense("input_d");

    SparseMatrix sA = read_sparse("input_a");
    SparseMatrix sB = read_sparse("input_b");
    SparseMatrix sC = read_sparse("input_c");
    SparseMatrix sD = read_sparse("input_d");

    cout << "--- Testing Add ---" << endl;
    DenseMatrix dAdd = dA + dB;
    SparseMatrix sAdd = sA + sB;
    if (verify(dAdd, sAdd, "expected_add"))
        cout << "SUCCESS" << endl;
    else
        cout << "FAILED" << endl;

    cout << "--- Testing Sub ---" << endl;
    DenseMatrix dSub = dA - dB;
    SparseMatrix sSub = sA - sB;
    if (verify(dSub, sSub, "expected_sub"))
        cout << "SUCCESS" << endl;
    else
        cout << "FAILED" << endl;

    cout << "--- Testing Mul ---" << endl;
    DenseMatrix dMul = dC * dD;
    SparseMatrix sMul = sC * sD;
    if (verify(dMul, sMul, "expected_mul"))
        cout << "SUCCESS" << endl;
    else
        cout << "FAILED" << endl;

    cout << "--- Testing Div ---" << endl;
    DenseMatrix dDiv = dA / dB;
    SparseMatrix sDiv = sA / sB;
    if (verify(dDiv, sDiv, "expected_div"))
        cout << "SUCCESS" << endl;
    else
        cout << "FAILED" << endl;

    cout << "--- Testing Transpose ---" << endl;
    DenseMatrix dTrans = dA.transpose();
    SparseMatrix sTrans = sA.transpose();
    if (verify(dTrans, sTrans, "expected_trans"))
        cout << "SUCCESS" << endl;
    else
        cout << "FAILED" << endl;

    return 0;
}
