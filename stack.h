#pragma once
#include <vector>
#include <string>
class Stack {
private:
    std::string* arr;
    int capacity;
    int top;
public:
    Stack(int size);
    void Push(const std::string& elem);
    std::string Pop();
    std::string Top();
    void Print();
    bool IsEmpty();
    std::vector<std::string> ToVector();
};

