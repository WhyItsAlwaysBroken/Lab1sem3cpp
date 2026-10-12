#pragma once
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include "stack.h"
#include "Queue.h"
#include "SingleLinkedList.h"
#include "DoubleLinkedList.h"
#include "BinaryTree.h"
#include "array.h"
class FileInOut
{
private:
    static const int CAP = 100; // גלוסעטלמסעü

    std::map<std::string, MyArray*> arrays;
    std::map<std::string, Stack*>   stacks;
    std::map<std::string, Queue*>   queues;
    std::map<std::string, Node*>    flists;
    std::map<std::string, dlist>  llists;
    std::map<std::string, btNode*>  trees;

    MyArray& arr(const std::string& n);
    Stack& stk(const std::string& n);
    Queue& que(const std::string& n);

    static void WriteLine(std::ofstream& f, const std::string& type,const std::string& name, const std::vector<std::string>& v);
    static void PrintVector(const std::vector<std::string>& v);
public:
    void Load(const std::string& path);
    void Save(const std::string& path);
    int Execute(const std::string& query);

};

