#include <gtest/gtest.h>
#include "../include/Heap.h"


TEST(BinaryHeapTest, InsertAndGetMin) {
    BinaryHeap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);

    EXPECT_EQ(*heap.getMax(), 20);
}

TEST(BinaryHeapTest, ExtractMin) {
    BinaryHeap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);

    EXPECT_EQ(*heap.extractMax(), 20);
    EXPECT_EQ(*heap.getMax(), 10);
}

TEST(BinaryHeapTest, StringTest) {
    BinaryHeap<std::string> stringHeap;
    stringHeap.insert("apple");
    stringHeap.insert("orange");
    stringHeap.insert("banana");

    EXPECT_EQ(*stringHeap.getMax(), "orange");
    EXPECT_EQ(*stringHeap.extractMax(), "orange");
    EXPECT_EQ(*stringHeap.getMax(), "banana");
}