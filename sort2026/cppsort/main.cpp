#include <iostream>
#include <chrono>
#include <random>
#include "SortManager.h"

std::vector<int> generateRandomData(int size)
{
    // 랜덤 데이터
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (int i = 0; i < size; i++)
        data[i] = dis(gen);
    return data;
}

void measureTime(std::string name, void (*sortFunc)(std::vector<int> &), int size, const std::vector<int> &data)
{
    auto new_data = data;
    if (SortManager::isSorted(new_data))
    {
        std::cout << "already sorted" << std::endl;
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(new_data);
    auto end = std::chrono::high_resolution_clock::now();
    if (!SortManager::isSorted(new_data))
    {
        std::cout << "sort Failed" << std::endl;
        return;
    }
    std::chrono::duration<double> diff = end - start;
    std::cout << name << " (N=" << size << "): " << diff.count() << "s" << std::endl;
}

int main()
{
    int sizes[] = {100000, 125000, 150000, 175000, 200000};
    // 100000 이상의 데이터들을 순차적으로 정렬
    for (int size : sizes)
    {
        std::cout << "--- Testing size: " << size << " ---" << std::endl;
        auto data = generateRandomData(size);
        measureTime("Insertion Sort", SortManager::insertionSort, size, data);
        measureTime("Selection Sort", SortManager::selectionSort, size, data);
        measureTime("Bubble Sort", SortManager::bubbleSort, size, data);
    }
    return 0;
}