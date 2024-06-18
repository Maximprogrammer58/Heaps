#ifndef HEAP_INCLUDE_HEAPSORT_H
#define HEAP_INCLUDE_HEAPSORT_H

#include "../include/BinomialHeap.h"
#include "../include/Heap.h"

template<typename T>
std::vector<T> ascendingHeapSort(std::vector<T>& data) {
    BinomialHeap<T> heap(data);

    std::vector<T> sorted;
    while (!heap.empty()) {
        sorted.push_back(*heap.extractMin());
    }
    return sorted;
}

template<typename T>
std::vector<T> descendingHeapSort(std::vector<T>& data) {
    BinaryHeap<T> heap(data);

    std::vector<T> sorted;
    while (!heap.empty()) {
        sorted.push_back(*heap.extractMax());
    }
    return sorted;
}

#endif