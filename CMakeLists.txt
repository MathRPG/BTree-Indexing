cmake_minimum_required(VERSION 3.17)
project(B_Tree_Indexing)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(BTree_Testing src/tests.cpp src/BTree.cpp src/Article.cpp src/Node.cpp)
add_executable(BTree_Release src/main.cpp src/BTree.cpp src/Article.cpp src/Node.cpp)
