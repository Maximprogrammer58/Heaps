#include <gtest/gtest.h>
#include "../include/FibonacciHeap.h"

TEST(FibonacciHeapTest, InsertAndGetMin) {
    FibonacciHeap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);

    EXPECT_EQ(*heap.getMin(), 5);
}

TEST(FibonacciHeapTest, ExtractMin) {
    FibonacciHeap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);

    EXPECT_EQ(*heap.extractMin(), 5);
    EXPECT_EQ(*heap.getMin(), 10);
}

TEST(FibonacciHeap, StringTest) {
    FibonacciHeap<std::string> stringHeap;
    stringHeap.insert("apple");
    stringHeap.insert("orange");
    stringHeap.insert("banana");

    EXPECT_EQ(*stringHeap.getMin(), "apple");
    EXPECT_EQ(*stringHeap.extractMin(), "apple");
    EXPECT_EQ(*stringHeap.getMin(), "banana");
}