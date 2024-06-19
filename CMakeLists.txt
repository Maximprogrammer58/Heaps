cmake_minimum_required(VERSION 3.11)

project(Heap CXX)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")   
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()


add_library(Heap SHARED "include/Heap.h" "src/Heap.cc")
target_include_directories(Heap PUBLIC "include")

add_library(BinomialHeap SHARED "include/BinomialHeap.h" "src/BinomialHeap.cc")
target_include_directories(BinomialHeap PUBLIC "include")

add_library(HeapSort SHARED "include/HeapSort.h" "src/HeapSort.cc")
target_include_directories(HeapSort PUBLIC "include")

add_library(FibonacciHeap SHARED "include/FibonacciHeap.h" "src/FibonacciHeap.cc")
target_include_directories(FibonacciHeap PUBLIC "include")

add_library(Graph SHARED "include/Graph.h" "src/Graph.cc")
target_include_directories(Graph PUBLIC "include")

add_executable(main "main.cc")
target_link_libraries(main Heap BinomialHeap FibonacciHeap)

add_executable(GraphTest "tests/Graph_test.cpp")
target_link_libraries(GraphTest FibonacciHeap Graph)

add_executable(Sorting "tests/Sort.cpp")
target_link_libraries(Sorting BinomialHeap Heap HeapSort)