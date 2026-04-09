#ifndef SORT_MANAGER_H
#define SORT_MANAGER_H

#include <vector>
#include <string>

class SortManager
{
public:
    static void bubbleSort(std::vector<int> &A);
    static void insertionSort(std::vector<int> &A);
    static void selectionSort(std::vector<int> &A);

    static std::vector<int> generateRandomData(int size);
    static bool isSorted(int *arr, int size);
};

#endif
