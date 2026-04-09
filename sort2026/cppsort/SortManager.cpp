#include "SortManager.h"
#include <algorithm>
#include <random>
// 이 파일은 독립된 알고리즘 파일임
void SortManager::bubbleSort(std::vector<int> &A)
{
    int n = A.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                std::swap(A[j], A[j + 1]);
            }
        }
    }
}

void SortManager::insertionSort(std::vector<int> &A)
{
    int n = A.size();
    for (int i = 1; i < n; i++)
    {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void SortManager::selectionSort(std::vector<int> &A)
{
    int n = A.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[min_idx])
                min_idx = j;
        }
        std::swap(A[i], A[min_idx]);
    }
}

bool SortManager::isSorted(int *arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return false; // 앞의 원소가 뒤의 원소보다 크면 정렬되지 않은 상태
        }
    }
    return true; // 끝까지 통과하면 정렬된 상태
}
