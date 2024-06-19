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

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

add_executable(HeapTimeTest "tests/Heaps_time_test.cpp")
target_link_libraries(HeapTimeTest Heap BinomialHeap FibonacciHeap)

add_executable(GraphTest "tests/Graph_test.cpp")
target_link_libraries(GraphTest FibonacciHeap Graph)

add_executable(Sorting "tests/Sort.cpp")
target_link_libraries(Sorting BinomialHeap Heap HeapSort)

add_executable(BinomialHeapTest "tests/BinomialHeapTest.cpp")
target_link_libraries(BinomialHeapTest BinomialHeap GTest::gtest_main)

add_executable(BinaryHeapTest "tests/BinaryHeapTest.cpp")
target_link_libraries(BinaryHeapTest Heap GTest::gtest_main)

add_executable(FibonacciHeapTest "tests/FibonacciHeapTest.cpp")
target_link_libraries(FibonacciHeapTest FibonacciHeap GTest::gtest_main)