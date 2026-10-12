#include "array.h"
#include <iostream>
using namespace std;
MyArray::MyArray(int size) {
	capacity = size;
	this->size = 0;
	arr = new string[capacity];
}
//написать функцию расширения вместимости массива
void MyArray::Insert(int index, const string& elem) {
	if (index < 0 || index > size){
		cout << "Out of range" << endl;
		return;
	}
	if (size >= capacity){
		cout << "Overflow" << endl;
		return;
	}
	//сдвиг элементов вправо
	for (int i = size; i >= index; i--){
		arr[i] = arr[i - 1];
	}
	arr[index] = elem;
	size++;
}
void MyArray::PushBack(const string& elem) {
	if (size >= capacity) {
		cout << "Overflow" << endl;
		return;
	}
	arr[size++] = elem;
}
string MyArray::Get(int index) {
	if (index < 0 || index > size) {
		cout << "Out of range" << endl;
		return "";
	}
	return arr[index];
}
string MyArray::PopIndex(int index) {
	if (index < 0 || index > size) {
		cout << "Out of range" << endl;
		return "";
	}
	string removed = arr[index];
	//сдвиг влево
	for (int i = index; i < size - 1;i++)
	{
		arr[i] = arr[i + 1];
	}
	size--;
	return removed;
}
string MyArray::Set(int index, const string& elem) {
	if (index < 0 || index >= size) {
		cout << "Out of range" << endl;
		return "";
	}
	return arr[index] = elem;
}
int MyArray::Length() {
	return size;
}
void MyArray::Print() {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
vector<string> MyArray::ToVector() {
	return vector<string>(arr, arr + size);
}
