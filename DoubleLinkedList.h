#pragma once
#include <vector>
#include <string>
class dbNode;
struct dlist {
	dbNode* head = nullptr;
	dbNode* tail = nullptr;
};
class dbNode
{
private:
	std::string data;
public:
	dbNode* left;
	dbNode* right;
	dbNode(const std::string& data);
	std::string Data() const { return data; }
	static void PushFront(dlist& list, const std::string& data);
	static void PushBack(dlist& list,  const std::string& data);
	static void InsertBefore(dlist& list,const std::string& target, const std::string& data);
	static void InsertAfter(dlist& list, const std::string& target, const std::string& data);
	static void PrintIter(dlist& list);
	static void PrintBack(dlist& list);
	static void RemoveValue(dlist& list, const std::string& target);
	static void RemoveFront(dlist& list);
	static void RemoveBack(dlist& list);
	static void RemoveBefore(dlist& list, const std::string& target);
	static void RemoveAfter(dlist& list, const std::string& target);
	static bool SearchValue(dlist& list, const std::string& target);
	static std::vector<std::string> ToVector(dlist& list);
};

