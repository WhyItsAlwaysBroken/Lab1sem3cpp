#include "stack.h"
#include <iostream>
using namespace std;

Stack::Stack(int size) {
    capacity = size;
    arr = new string[capacity];
    top = -1;
}
void Stack::Push(const string& elem) {
    if (top == capacity - 1) {
        cout << "Stack Overflow" << endl;
        return;
    }
    arr[++top] = elem;
}
std::string Stack::Pop() {
    if (top == -1) {
        cout << "Stack Underflow" << endl;
        return "";
    }
    return arr[top--];
}
string Stack::Top() {
    if (top == -1){
        cout << "Stack Underflow" << endl;
        return "";
    }
    return arr[top];
}
void Stack::Print() {
    if (top == -1) {
        cout << "Stack Underflow" << endl;
    }
    for (int i = top; i >= 0; --i) {
        cout << arr[i] << endl;
    }
}
bool Stack::IsEmpty() {
    return top == -1;
}
vector<string> Stack::ToVector() {
    return vector<string>(arr, arr + top + 1);
}
