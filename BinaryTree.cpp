#include "BinaryTree.h"


btNode::btNode(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
};
//вставка элемента
btNode* btNode::InsertNode(btNode * root, int data) {

    //если пустое создаем корень
    if (root == nullptr) {
        root = new btNode(data);
        return root;
    }
    //ищем по уровням свободное место
    queue<btNode*> q;
    q.push(root);

    while (!q.empty()) {

        //первый в очереди
        btNode* curr = q.front();
        q.pop();

        // сначала проверяем левую сторону затем правую
        if (curr->left != nullptr)
            q.push(curr->left);
        else {
            curr->left = new btNode(data);
            return root;
        }

        if (curr->right != nullptr)
            q.push(curr->right);
        else {
            curr->right = new btNode(data);
            return root;
        }
    }
    return root;
}
//Inorder обход
void btNode::inOrder(btNode* curr) {
    if (curr == nullptr)
        return;
    inOrder(curr->left);
    cout << curr->data << ' ';
    inOrder(curr->right);
}
//dfs (preorder) обход
void btNode::dfs(btNode* root, vector<int>& res) {
    if (root == nullptr) return;

    res.push_back(root->data); // Посещаем корень
    dfs(root->left, res);      // Рекурсивно идём влево
    dfs(root->right, res);     // Рекурсивно идём вправо
}
//bfs обход
vector<int> btNode::bfs(btNode* root) {
    vector<int> res;
    if (root == nullptr) return res;

    queue<btNode*> q;
    q.push(root);

    while (!q.empty()) {
        btNode* curr = q.front();
        q.pop();

        res.push_back(curr->data); // Записываем значение текущего узла

        if (curr->left != nullptr)
            q.push(curr->left);   // Кладем левого ребенка в очередь

        if (curr->right != nullptr)
            q.push(curr->right);  // Кладем правого ребенка в очередь
    }

    return res;
}
bool btNode::searchNode(btNode* root, int target) {
    if (root == nullptr) return false; 
    if (root->data == target) return true;
    // Рекурсивно ищем в левом и правом поддереве
    return searchNode(root->left, target) || searchNode(root->right, target);
}
bool btNode::isComplete(btNode* root) {
    if (root == nullptr) return true;

    queue<btNode*> q;
    q.push(root);
    bool flag = false; //пустой потомок
    while (!q.empty()) {
        btNode* curr = q.front();
        q.pop();
        //пока слева не пусто
        if (curr->left != nullptr) {
            if (flag) return false;
            q.push(curr->left);   // Кладем левого ребенка в очередь
        }
        else {
            flag = true;
        }
        //пока справа не пусто
        if (curr->right != nullptr)
        {
            if (flag) return false;
            q.push(curr->right);  // Кладем правого ребенка в очередь
        }
        else {
            flag = true;
        }
    }
    return true;

}


