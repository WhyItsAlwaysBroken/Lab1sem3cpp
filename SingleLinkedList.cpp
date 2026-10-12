#include "SingleLinkedList.h"
#include  <iostream>
using namespace std;
Node::Node(const string& data) {
	this->data = data;
	next = nullptr;
}
void Node::PushFront(Node*& head, const string& data) {
	Node* temp = head;
	head = new Node(data);
	head->next = temp;
}
void Node::PushBack(Node*& head, const string& data) {
	Node* NewNode = new Node(data);
	//если указатель с головы пуст
	if (head == nullptr) {
		head = NewNode;
		return;
	}
	Node* current = head;
	//иначе ищем конец списка
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = NewNode;
}
void Node::InsertBefore(Node*& head, const string& target, const string& data) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	if (head->data == target) {
		PushFront(head, data);
		return;
	}
	Node* current = head;
	while (current->next != nullptr && current->next->data != target) {
		current = current->next;
	}
	if (current->next == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	Node* newNode = new Node(data);
	newNode->next = current->next;
	current->next = newNode;
}
void Node::InsertAfter(Node*& head, const string& target, const string& data) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	Node* current = head;
	while (current != nullptr && current->data != target) {
		current = current->next;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	Node* newNode = new Node(data);
	newNode->next = current->next;
	current->next = newNode;
}
void Node::PrintIter(Node*& head) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	Node* temp = head;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}
static void PrintRecurHelper(Node* node) {
	if (node == nullptr) return;
	PrintRecurHelper(node->next);
	cout << node->Data() << " ";

}
void Node::PrintRecur(Node*& head) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	PrintRecurHelper(head);
}
void Node::RemoveValue(Node*& head, const string& target) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	if (head->data == target) {
		Node* temp = head;
		head = head->next;
		delete temp;
		return;
	}
	Node* current = head;
	while (current->next != nullptr && current->next->data != target) {
		current = current->next;
	}
	if (current->next == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	Node* temp = current->next;
	current->next = temp->next;
	delete temp;
}
void Node::RemoveFront(Node*& head) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	Node* temp = head;
	head = head->next;
	delete temp;
}
void Node::RemoveBack(Node*& head) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}
	Node* current = head;
	//предпоследний узел
	while (current->next->next != nullptr) {
		current = current->next;
	}
	//удаляем последний
	delete current->next;
	current->next = nullptr;
}
void Node::RemoveBefore(Node*& head, const string& target) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	if (head->data == target) {
		cout << "There is no element before " << target << endl;
		return;
	}
	Node* prev = nullptr;
	Node* current = head;
	while (current->next != nullptr && current->next->data != target) {
		prev = current;
		current = current->next;
	}
	if (current->next == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	// current - узел перед искомым
	if (prev == nullptr) head = current->next;
	else prev->next = current->next;
	delete current;
}
void Node::RemoveAfter(Node*& head, const string& target) {
	if (head == nullptr) {
		cout << "Underflow" << endl;
		return;
	}
	Node* current = head;
	while (current != nullptr && current->data != target) {
		current = current->next;
	}
	if (current == nullptr) {
		cout << "There is no " << target << " value" << endl;
		return;
	}
	if (current->next == nullptr) {
		cout << "There is no element after " << target << endl;
		return;
	}
	Node* temp = current->next;
	current->next = temp->next;
	delete temp;
}
bool Node::SearchValue(Node*& head, const string& target) {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == target) {
			return true;
		}
		current = current->next;
	}
		return false;
}
vector<string> Node::ToVector(Node* head) {
	vector<string> v;
	Node* current = head;
	while (current != nullptr) {
		v.push_back(current->data);
		current = current->next;
	}
	return v;
}