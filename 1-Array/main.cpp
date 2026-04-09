#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void testMatrixOperations(int M, int N, int K, int pct)
{
    cout << "\n======================================" << endl;
    cout << "  Test Matrix Size: " << M << "x" << N << " (Mul: " << M << "x" << K << " * " << K << "x" << N << ")" << " Density: " << pct << "%" << endl;
    cout << "======================================" << endl;

    DenseMatrix d1(M, N), d2(M, N), d3(M, K), d4(K, N);
    SparseMatrix s1(M, N), s2(M, N), s3(M, K), s4(K, N);

    // 랜덤 데이터 채우기 (희소성: 약 5% 확률로 0이 아닌 값)
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (rand() % 100 < pct)
            {
                double val = (rand() % 100) + 1;
                d1.setValue(i, j, val);
                s1.addElement(i, j, val);
            }
            if (rand() % 100 < pct)
            {
                double val = (rand() % 100) + 1;
                d2.setValue(i, j, val);
                s2.addElement(i, j, val);
            }
        }
    }
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            if (rand() % 100 < pct)
            {
                double val = (rand() % 100) + 1;
                d3.setValue(i, j, val);
                s3.addElement(i, j, val);
            }
        }
    }
    for (int i = 0; i < K; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (rand() % 100 < pct)
            {
                double val = (rand() % 100) + 1;
                d4.setValue(i, j, val);
                s4.addElement(i, j, val);
            }
        }
    }

    // --- 덧셈(Add) ---
    auto start = system_clock::now();
    DenseMatrix dAdd = d1 + d2;
    auto end = system_clock::now();
    cout << "[Dense Add]      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = system_clock::now();
    SparseMatrix sAdd = s1 + s2;
    end = system_clock::now();
    cout << "[Sparse Add]     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    // --- 뺄셈(Sub) ---
    start = system_clock::now();
    DenseMatrix dSub = d1 - d2;
    end = system_clock::now();
    cout << "[Dense Sub]      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = system_clock::now();
    SparseMatrix sSub = s1 - s2;
    end = system_clock::now();
    cout << "[Sparse Sub]     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    // --- 곱셈(Multiply) ---
    start = system_clock::now();
    DenseMatrix dMul = d3 * d4;
    end = system_clock::now();
    cout << "[Dense Mul]      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = system_clock::now();
    SparseMatrix sMul = s3 * s4;
    end = system_clock::now();
    cout << "[Sparse Mul]     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    // --- 나눗셈(Division - Element-wise) ---
    start = system_clock::now();
    DenseMatrix dDiv = d1 / d2;
    end = system_clock::now();
    cout << "[Dense Div]      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = system_clock::now();
    SparseMatrix sDiv = s1 / s2;
    end = system_clock::now();
    cout << "[Sparse Div]     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    // --- 전치(Transpose) ---
    start = system_clock::now();
    DenseMatrix dTrans = d1.transpose();
    end = system_clock::now();
    cout << "[Dense Trans]    " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = system_clock::now();
    SparseMatrix sTrans = s1.transpose();
    end = system_clock::now();
    cout << "[Sparse Trans]   " << duration_cast<microseconds>(end - start).count() << " us" << endl;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    // 테스트할 행렬 크기 배열 {M, N, K}
    int sizes[][3] = {
        {10, 10, 10},
        {50, 50, 50},
        {100, 100, 100},
        {200, 200, 200},
        {500, 500, 500},
        {1000, 1000, 1000},
    };

    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < numTests; ++j)
        {
            testMatrixOperations(sizes[j][0], sizes[j][1], sizes[j][2], i);
        }
    }

    return 0;
}
