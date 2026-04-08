#include <iostream>
#include <chrono>
#include "SortManager.h"

void measureTime(std::string name, void (*sortFunc)(std::vector<int>&), int size) {
    auto data = SortManager::generateRandomData(size);
   
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = std::chrono::high_resolution_clock::now();
   
    std::chrono::duration<double> diff = end - start;
    std::cout << name << " (N=" << size << "): " << diff.count() << "s" << std::endl;
}

int main() {
    int sizes[] = {100000, 125000, 150000, 175000, 200000};
    //100000 이상의 데이터들을 순차적으로 정렬
    for (int size : sizes) {
        std::cout << "--- Testing size: " << size << " ---" << std::endl;
        measureTime("Insertion Sort", SortManager::insertionSort, size);
        measureTime("Selection Sort", SortManager::selectionSort, size);
        measureTime("Bubble Sort", SortManager::bubbleSort, size);
    }
    return 0;
}