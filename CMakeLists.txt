cmake_minimum_required(VERSION 3.17)
project(B_Tree_Indexing)

set(CMAKE_CXX_STANDARD 17)

add_executable(B_Tree_Indexing main.cpp Article.cpp B_Tree.cpp)
add_executable(B_Tree_Testing tests.cpp Article.cpp B_Tree.cpp)