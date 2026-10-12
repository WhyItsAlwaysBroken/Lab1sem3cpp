#include "DoubleLinkedList.h"
#include "iostream"
using namespace std;

dbNode::dbNode(const string& data) {
	this->data = data;
	left = nullptr;
	right = nullptr;
}
void dbNode::PushFront(dlist& list, const string& data) {
	dbNode* newNode = new dbNode(data);
	newNode->right = list.head;
	if (list.head != nullptr) {
		list.head->left = newNode;
	}
	else
	{
		list.head = newNode;
		list.tail = newNode;

	}
}
void dbNode::PushBack(dlist& list, const string& data) {
	dbNode* NewNode = new dbNode(data);
	if (list.tail == nullptr) {
		list.head = NewNode;
		list.tail = NewNode;
		return;
	}
	NewNode->left = list.tail;
	list.tail->right = NewNode;
	list.tail = NewNode;
}
void dbNode::InsertBefore(dlist& list, const string& target, const string& data) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	if (list.head->data == target) {
		PushFront(list, data);
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr && current->data != target) {
		current = current->right;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	dbNode* newNode = new dbNode(data);
	newNode->right = current	;
	newNode->left = current->left;
	current->left->right = newNode;
	current->left = newNode;
}
void dbNode::InsertAfter(dlist& list, const string& target, const string& data) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr && current->data != target) {
		current = current->right;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	if (current == list.tail) {
		PushBack(list, data);
		return;
	}
	dbNode* newNode = new dbNode(data);
	newNode->right = current->right;
	newNode->left = current;
	current->right->left = newNode;
	current->right = newNode;

}
void dbNode::PrintIter(dlist& list) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->right;
	}
	cout << endl;

}
void dbNode::PrintBack(dlist& list) {
	if (list.tail == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.tail;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->left;
	}
	cout << endl;

}
void dbNode::RemoveValue(dlist& list, const string& target) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr && current->data != target) {
		current = current->right;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	if (current == list.head) {
		RemoveFront(list);
		return;
	}
	if (current == list.tail) {
		RemoveBack(list);
		return;
	}
	current->left->right = current->right;
	current->right->left = current->left;
	delete current;
}
void dbNode::RemoveFront(dlist& list) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* temp = list.head;
	list.head = list.head->right;
	if (list.head != nullptr) list.head->left = nullptr;
	else list.tail = nullptr;
	delete temp;
}
void dbNode::RemoveBack(dlist& list) {
	if (list.tail == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.tail;
	list.tail = list.tail->left;
	if (list.tail != nullptr) {
		list.tail->right = nullptr;
	}
	else list.head = nullptr;
	delete current;
}
void dbNode::RemoveBefore(dlist& list, const string& target) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr && current->data != target) {
		current = current->right;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	if (current->left == nullptr) {
		cout << "There is no element before " << target << endl;
		return;
	}
	dbNode* temp = current->left;
	if (temp->left != nullptr) temp->left->right = current;
	else list.head = current;
	current->left = temp->left;
	delete temp;
}
void dbNode::RemoveAfter(dlist& list, const string& target) {
	if (list.head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	dbNode* current = list.head;
	while (current != nullptr && current->data != target) {
		current = current->right;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	if (current->right == nullptr) {
		cout << "There is no element after " << target << endl;
		return;
	}
	dbNode* temp = current->right;
	current->right = temp->right;
	if (temp->right != nullptr) temp->right->left = current;
	else list.tail = current;
	delete temp;
}
bool dbNode::SearchValue(dlist& list, const string& target) {
	dbNode* current = list.head;
	while (current != nullptr) {
		if (current->data == target) {
			return true;
		}
		current = current->right;
	}
	return false;
}
vector<string> dbNode::ToVector(dlist& list) {
	vector<string> v;
	dbNode* current = list.head;
	while (current != nullptr) {
		v.push_back(current->data);
		current = current->right;
	}
	return v;
}