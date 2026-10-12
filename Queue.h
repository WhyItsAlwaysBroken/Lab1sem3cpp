#pragma once
#include <vector>
#include <string>
class Queue
{
private:
	std::string* arr;
	int capacity;
	int front;
	int rear;
public:
	Queue(int size);
	void push(const std::string& elem);
	std::string pop();
	std::string frontElem();
	std::string rearElem();
	void Print();
	bool IsEmpty();
	std::vector<std::string> ToVector();
};

