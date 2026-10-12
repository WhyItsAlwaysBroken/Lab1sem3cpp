#pragma once
#include <vector>
#include <string>
using namespace std;
class MyArray
{
private:
	string* arr;
	int capacity; //вместимость
	int size; //текущее кол-во элементов
public:
	MyArray(int capacity);
	void Insert(int index, const string& elem);
	void PushBack(const string& elem);
	string Get(int index);
	string PopIndex(int index);
	string Set(int index, const string& elem);
	int Length();
	void Print();
	std::vector<string> ToVector();


};

