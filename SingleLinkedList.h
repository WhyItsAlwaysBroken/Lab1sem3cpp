#pragma once
#include <vector>
#include <string>
class Node
{
private:
	std::string data;
public:
	Node* next;
	Node(const std::string& data);
	std::string Data() const { return data; }
	static void PushFront(Node*& head, const std::string& data);
	static void PushBack(Node*& head, const std::string& data);
	static void InsertBefore(Node*& head, const std::string& target, const std::string& data);
	static void InsertAfter(Node*& head, const std::string& target, const std::string& data);
	static void PrintIter(Node*& head);
	static void PrintRecur(Node*& head);
	static void RemoveValue(Node*& head, const std::string& target);
	static void RemoveFront(Node*& head);
	static void RemoveBack(Node*& head);
	static void RemoveBefore(Node*& head, const std::string& target);
	static void RemoveAfter(Node*& head, const std::string& target);
	static bool SearchValue(Node*& head, const std::string& target);
	static std::vector<std::string> ToVector(Node* head);
};

