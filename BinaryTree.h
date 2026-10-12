#pragma once
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
class btNode
{
public:
	int data;
	btNode* left;
	btNode* right;
	btNode(int data);
	static btNode* InsertNode(btNode* root, int data);
	static void inOrder(btNode* curr);
	static void dfs(btNode* root, vector<int>& res);
	static vector<int> bfs(btNode* root);
	static bool searchNode(btNode* root, int target);
	static bool isComplete(btNode* root);
};