cmake_minimum_required(VERSION 3.22)
project(Trabalho_1_Refatorado)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trabalho_1_Refatorado main.cpp
        lib/include/Edge.h lib/src/Edge.cpp
        lib/include/Node.h lib/src/Node.cpp
        lib/include/Graph.h lib/src/Graph.cpp lib/include/Sort.h lib/src/Sort.cpp lib/include/GraphOperations.h lib/src/GraphOperations.cpp lib/include/PriorityQueue.h lib/include/PriorityQueue.h)
