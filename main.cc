#include "include/HeapSort.h"

template <typename T>
void print(const std::vector<T>& data) {
	for (const T& value : data) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
}

int main() {
	setlocale(LC_ALL, "Rus");
	std::vector data = { 5, 6, 0, 1, 9, 18, 10 };
	std::cout << "Результаты" << std::endl;
	std::cout << "Исходный массив: ";
	print(data);
	std::cout << "После HeapSort: ";
	print(ascendingHeapSort(data));
	std::vector<int> mas = { 13, 42, 90, 74, 51, 14, 60, 8, 15 };
	BinaryHeap<int> heap(mas);
	heap.print();
	std::optional<int> max = heap.extractMax();
	if (max) {
		std::cout << *max << std::endl;
	}
	heap.print();
	heap.insert(98);
	heap.print();
	std::cout << "..........................." << std::endl;
	BinomialHeap<int> b_heap(mas);
	std::cout << *b_heap.extractMin() << std::endl;
	std::cout << *b_heap.extractMin() << std::endl;
}