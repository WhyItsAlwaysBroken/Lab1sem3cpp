#include "Queue.h"
#include <iostream>
using namespace std;
Queue::Queue(int size)
{
	capacity = size;
	arr = new string[capacity];
	front = -1;
	rear = -1;
}
void Queue::push(const string& elem) {
	if (rear == capacity - 1) {
		cout << "Overflow" << endl;
		return;
	}
	if (front == -1) {
		front = 0;
		rear = 0;
	}
	else {
		rear++;
	}
	arr[rear] = elem;
}
string Queue::pop() {
	if (front == -1) {
		cout << "Underflow" << endl;
		return "";
	}
	string temp = arr[front];
	if (front == rear) {
		front = -1;
		rear = -1;
	}
	else {
		front++;
	}
	return temp;
}
string Queue::frontElem() {
	if (front == -1) {
		cout << "queue is Empty" << endl;
		return "";
	}
	return arr[front];
}
string Queue::rearElem() {
	if (front == -1) {
		cout << "queue is Empty" << endl;
		return "";
	}
	return arr[rear];
}
bool Queue::IsEmpty() {
	return front == -1;
}
void Queue::Print() {
	if (front > rear || front == -1) {
		cout << "Queue is empty" << endl;
		return;
	}
	for (int i = front; i <= rear; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
vector<string> Queue::ToVector() {
	if (front == -1) return vector<string>();
	return vector<string>(arr + front, arr + rear + 1);
}