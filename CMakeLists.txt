cmake_minimum_required(VERSION 3.17)
project(B_Tree_Indexing)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(BTree_Testing src/tests.cpp src/BTree.cpp src/BTree.h src/Article.cpp src/Article.h src/Node.cpp src/Node.h)
