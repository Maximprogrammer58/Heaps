#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <random>

#include "../include/HeapSort.h"
#include "../include/FibonacciHeap.h"
#include "../include/Graph.h"


int main() {
    const int NUM_EXPERIMENTS = 10;

    Graph<int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);
    graph.add_vertex(6);
    graph.add_vertex(7);
    graph.add_vertex(8);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(4, 2, 1);
    graph.add_edge(4, 3, 3);
    graph.add_edge(3, 5, 4);
    graph.add_edge(1, 3, 4);
    graph.add_edge(5, 4, 5);

    graph.print();

    double distance = 0.0;
    std::cout << "Dijkstra's algorithm" << std::endl;
    for (const auto& edge : graph.shortest_path(1, 4)) {
        std::cout << "From " << edge.from << " to " << edge.to << " distance = " << edge.distance << std::endl;
        distance += edge.distance;
    }
    std::cout << "Distance from 1 to 4 =  " << distance << std::endl;

    distance = 0.0;
    std::cout << "Dijkstra's algorithm" << std::endl;
    for (const auto& edge : graph.shortest_path_with_heap(1, 4)) {
        std::cout << "From " << edge.from << " to " << edge.to << " distance = " << edge.distance << std::endl;
        distance += edge.distance;
    }
    std::cout << "Distance from 1 to 4 =  " << distance << std::endl;


    double time1 = 0;
    for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        graph.shortest_path(1, 4);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        time1 += elapsed.count();
    }
    std::cout << "Priority Queue: " << time1 / NUM_EXPERIMENTS << " ms" << std::endl;

    double time2 = 0;
    for (int i = 0; i < NUM_EXPERIMENTS; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        graph.shortest_path_with_heap(1, 4);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        time2 += elapsed.count();
    }
    std::cout << "Fibonacci Heap: " << time2 / NUM_EXPERIMENTS << " ms" << std::endl;

    return 0;
}