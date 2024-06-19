#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <random>

#include "../include/HeapSort.h" 

template <typename T>
double measureTimeSort(std::vector<T>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    descendingHeapSort(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

template <typename T>
void print(const std::vector<T>& data) {
    for (const T& value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    
    for (int num = 1000; num <= 50000; num += 5000) {
        std::vector<int> ascending_data(num);
        for (int i = 0; i < num; i++) {
            ascending_data[i] = i + 1;
        }
        std::cout << "SIZE: " << num << std::endl;
        std::cout << "Ascending HeapSort: " << measureTimeSort(ascending_data) << std::endl;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        std::vector<int> data(num);
        for (int& i : data) {
            i = dis(gen);
        }
        std::cout << "SIZE: " << num << std::endl;
        std::cout << "Random HeapSort: " << measureTimeSort(data) << std::endl;

        std::vector<int> descending_data(num);
        for (int i = 0; i < num; i++) {
            descending_data[i] = num - i;
        }
        std::cout << "SIZE: " << num << std::endl;
        std::cout << "Descending HeapSort: " << measureTimeSort(descending_data) << std::endl;
    }

    std::vector<int> data(10);
 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);;
    for (int& i : data) {
        i = dis(gen);
    }
    std::cout << "Vector: ";
    print(data);
    std::cout << "Sorted using BinaryMaxHeap: ";
    print(descendingHeapSort(data));
    std::cout << "Sorted using BinomailMinHeap: ";
    print(ascendingHeapSort(data));

	return 0;
}