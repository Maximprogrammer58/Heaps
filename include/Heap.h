#ifndef HEAP_INCLUDE_HEAP_H
#define HEAP_INCLUDE_HEAP_H

#include <iostream>
#include <vector>
#include <optional>
#include <functional>

template<typename T, typename Comparator = std::less<T>>
class BinaryHeap {
    std::vector<T> _heap;
    Comparator _comp;

    size_t parent(size_t i) {
        return (i - 1) / 2;
    }

    size_t left(size_t i) {
        return 2 * i + 1;
    }

    size_t right(size_t i) {
        return 2 * i + 2;
    }

    void siftUp(size_t i) {
        while (i > 0 && _comp(_heap[parent(i)], _heap[i])) {
            std::swap(_heap[parent(i)], _heap[i]);
            i = parent(i);
        }
    }

    void siftDown(size_t i) {
        size_t largest = i;
        size_t l = left(i);
        size_t r = right(i);

        if (l < _heap.size() && _comp(_heap[largest], _heap[l])) {
            largest = l;
        }
        if (r < _heap.size() && _comp(_heap[largest], _heap[r])) {
            largest = r;
        }

        if (largest != i) {
            std::swap(_heap[i], _heap[largest]);
            siftDown(largest);
        }
    }

public:
    BinaryHeap() : _comp(Comparator()) {}

    explicit BinaryHeap(const std::vector<T>& data, Comparator comp = Comparator())
        : _comp(comp) {
        for (const T& value : data) {
            insert(value);
        }
    }

    void insert(const T& value) {
        _heap.push_back(value);
        siftUp(_heap.size() - 1);
    }

    std::optional<T> getMax() const {
        if (_heap.empty()) {
            return std::nullopt;
        }
        return _heap[0];
    }

    std::optional<T> extractMax() {
        if (_heap.empty()) {
            return std::nullopt;
        }

        T max = _heap[0];
        _heap[0] = _heap.back();
        _heap.pop_back();
        siftDown(0);
        return max;
    }

    void remove(size_t i) {
        if (i >= _heap.size()) {
            return;
        }

        _heap[i] = _heap.back();
        _heap.pop_back();
        siftDown(i);
    }

    void updateValue(size_t i, const T& newValue) {
        if (i >= _heap.size()) {
            return;
        }

        T oldValue = _heap[i];
        _heap[i] = newValue;
        if (_comp(newValue, oldValue)) {
            siftDown(i);
        }
        else {
            siftUp(i);
        }
    }

    bool empty() const {
        return _heap.empty();
    }

    size_t size() const {
        return _heap.size();
    }

    void print() const {
        for (const auto& item : _heap) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

#endif