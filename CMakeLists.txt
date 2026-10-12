cmake_minimum_required(VERSION 3.30)
project(cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp main.cpp array.h array.cpp stack.h stack.cpp Queue.h Queue.cpp SingleLinkedList.h SingleLinkedList.cpp DoubleLinkedList.h DoubleLinkedList.cpp BinaryTree.h BinaryTree.cpp FileInOut.h FileInOut.cpp)
