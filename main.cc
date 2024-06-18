#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <random>

#include "include/HeapSort.h"
#include "include/FibonacciHeap.h"
#include "include/Graph.h"

template <typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

int main() {
    const int NUM_EXPERIMENTS = 20;

    for (int num = 1000; num <= 50000; num += 10000) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(1, 1000);

        std::vector<int> data(num);
        for (int& i : data) {
            i = dis(gen);
        }

        std::cout << "Insert" << std::endl;
        std::cout << "SIZE = " << num << std::endl;
        double HeapInsertTime = 0;
        for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
            BinaryHeap<int> heap;
            HeapInsertTime += measureTime([&]() {
                for (int x : data) {
                    heap.insert(x);
                }
                });
        }
        std::cout << "Binary Heap: " << HeapInsertTime / NUM_EXPERIMENTS << " ms" << std::endl;

        std::cout << "SIZE = " << num << std::endl;
        HeapInsertTime = 0;
        for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
            BinomialHeap<int> b_heap;
            HeapInsertTime += measureTime([&]() {
                for (int x : data) {
                    b_heap.insert(x);
                }
                });
        }
        std::cout << "Binomial Heap: " << HeapInsertTime / NUM_EXPERIMENTS << " ms" << std::endl;


        std::cout << "Extract min/max" << std::endl;
        std::cout << "SIZE = " << num << std::endl;
        double HeapExtractTime = 0;
        for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
            BinaryHeap<int> heap;
            HeapInsertTime += measureTime([&]() {
                for (int x : data) {
                    heap.extractMax();
                }
                });
        }
        std::cout << "Binary Heap: " << HeapExtractTime / NUM_EXPERIMENTS << " ms" << std::endl;

        std::cout << "SIZE = " << num << std::endl;
        HeapExtractTime = 0;
        for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
            BinomialHeap<int> b_heap;
            HeapInsertTime += measureTime([&]() {
                for (int x : data) {
                    b_heap.extractMin();
                }
                });
        }
        std::cout << "Binomial Heap: " << HeapExtractTime / NUM_EXPERIMENTS << " ms" << std::endl;
    }
}
