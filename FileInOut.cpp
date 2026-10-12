#include "FileInOut.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
using namespace std;
static vector<string> toString(const vector<int>& v) {
    vector<string> r;
    for (int x : v) {
        r.push_back(to_string(x));
    }
    return r;
}
enum class Cmd {
    // Array (M)
    MPUSH, MINS, MGET, MDEL, MSET, MLEN,
    // Single linked list (F)
    FPUSH, FPUSHFRONT, FINSBEFORE, FINSAFTER, FDEL, FDELFRONT, FDELBACK,
    FDELBEFORE, FDELAFTER, FFIND, FGET, FGETREC,
    // Double linked list (L)
    LPUSH, LPUSHFRONT, LINSBEFORE, LINSAFTER, LDEL, LDELFRONT, LDELBACK,
    LDELBEFORE, LDELAFTER, LFIND, LGET, LGETBACK,
    // Queue (Q)
    QPUSH, QGET, QPOP, QFRONT, QREAR,
    // Stack (S)
    SPUSH, SGET, SPOP, STOP,
    // Tree (T)
    TINSERT, TGET, TISCOMPLETE, TBFS, TDFS, TINORDER,
    // Print
    PRINT,
};
// Строка из запроса в команду
static const unordered_map<string, Cmd> COMMANDS = {
    {"MPUSH", Cmd::MPUSH}, {"MINS", Cmd::MINS}, {"MGET", Cmd::MGET},
    {"MDEL", Cmd::MDEL}, {"MSET", Cmd::MSET}, {"MLEN", Cmd::MLEN},

    {"FPUSH", Cmd::FPUSH}, {"FPUSHFRONT", Cmd::FPUSHFRONT},
    {"FINSBEFORE", Cmd::FINSBEFORE}, {"FINSAFTER", Cmd::FINSAFTER},
    {"FDEL", Cmd::FDEL}, {"FDELFRONT", Cmd::FDELFRONT}, {"FDELBACK", Cmd::FDELBACK},
    {"FDELBEFORE", Cmd::FDELBEFORE}, {"FDELAFTER", Cmd::FDELAFTER},
    {"FFIND", Cmd::FFIND}, {"FGET", Cmd::FGET}, {"FGETREC", Cmd::FGETREC},

    {"LPUSH", Cmd::LPUSH}, {"LPUSHFRONT", Cmd::LPUSHFRONT},
    {"LINSBEFORE", Cmd::LINSBEFORE}, {"LINSAFTER", Cmd::LINSAFTER},
    {"LDEL", Cmd::LDEL}, {"LDELFRONT", Cmd::LDELFRONT}, {"LDELBACK", Cmd::LDELBACK},
    {"LDELBEFORE", Cmd::LDELBEFORE}, {"LDELAFTER", Cmd::LDELAFTER},
    {"LFIND", Cmd::LFIND}, {"LGET", Cmd::LGET}, {"LGETBACK", Cmd::LGETBACK},

    {"QPUSH", Cmd::QPUSH}, {"QGET", Cmd::QGET}, {"QPOP", Cmd::QPOP},
    {"QFRONT", Cmd::QFRONT}, {"QREAR", Cmd::QREAR},

    {"SPUSH", Cmd::SPUSH}, {"SGET", Cmd::SGET}, {"SPOP", Cmd::SPOP}, {"STOP", Cmd::STOP},

    {"TINSERT", Cmd::TINSERT},
    {"TGET", Cmd::TGET}, {"ISMEMBER", Cmd::TGET},   // два имени на одну команду
    {"TISCOMPLETE", Cmd::TISCOMPLETE}, {"TBFS", Cmd::TBFS}, {"TDFS", Cmd::TDFS},
    {"TINORDER", Cmd::TINORDER},
    {"PRINT", Cmd::PRINT},
};
MyArray& FileInOut::arr(const string& n) { if (!arrays[n]) arrays[n] = new MyArray(CAP); return *arrays[n]; }
Stack& FileInOut::stk(const string& n) { if (!stacks[n]) stacks[n] = new Stack(CAP);   return *stacks[n]; }
Queue& FileInOut::que(const string& n) { if (!queues[n]) queues[n] = new Queue(CAP);   return *queues[n]; }

void FileInOut::Load(const string& path) {
    ifstream f(path);
    if (!f) return; //файла нет
    string line;
    while (getline(f, line)) {
        istringstream in(line);
        string type, name;
        if (!(in >> type >> name)) continue;
        if (type == "M") arr(name);
        else if (type == "S") stk(name);
        else if (type == "Q") que(name);
        else if (type == "F") flists[name];
        else if (type == "L") llists[name];
        else if (type == "T") trees[name];
        string v;
        while (in >> v) {
            if (type == "M") arr(name).PushBack(v);
            else if (type == "S") stk(name).Push(v);
            else if (type == "Q") que(name).push(v);
            else if (type == "F") Node::PushBack(flists[name], v);
            else if (type == "L") dbNode::PushBack(llists[name], v);
            else if (type == "T") {
                try {
                    trees[name] = btNode::InsertNode(trees[name], stoi(v));
                }
                catch (...) {}
            }
        }
    }
}

void FileInOut::WriteLine(ofstream& f, const string& type, const string& name, const vector<string>& v) {
    f << type << " " << name;
    for (const string& x : v) f << " " << x;
    f << "\n";
}

void FileInOut::Save(const string& path) {
    ofstream f(path);
    if (!f) { cerr << "Cannot write file " << path << endl; return; }
    for (auto& p : arrays) WriteLine(f, "M", p.first, p.second->ToVector());
    for (auto& p : stacks) WriteLine(f, "S", p.first, p.second->ToVector());
    for (auto& p : queues) WriteLine(f, "Q", p.first, p.second->ToVector());
    for (auto& p : flists) WriteLine(f, "F", p.first, Node::ToVector(p.second));
    for (auto& p : llists) WriteLine(f, "L", p.first, dbNode::ToVector(p.second));
    for (auto& p : trees)  WriteLine(f, "T", p.first, toString(btNode::bfs(p.second)));
}

void FileInOut::PrintVector(const vector<string>& v) {
    if (v.empty()) { cout << "Empty" << endl; return; }
    for (const string& x : v) cout << x << " ";
    cout << endl;
}

int FileInOut::Execute(const string& query) {
    istringstream in(query);
    string cmd, name;
    in >> cmd >> name;
    if (cmd.empty() || name.empty()) {
        cerr << "Query format CMD name [args]" << endl;
        return 1;
    }
    auto it = COMMANDS.find(cmd);
    if (it == COMMANDS.end()) {
        cerr << "Unknown command: " << cmd << endl;
        return 1;
    }
    string v, target;
    int idx = 0, num = 0;
    //лямбда функция список захвата читаем число и возвращаем бул
    auto need = [&](int& x) -> bool {
        if (!(in >> x)) { cerr << "Missing or invalid argument" << endl; return false; }
        return true;
    };
    auto needstr = [&](string& x) -> bool {
        if (!(in >> x)) { cerr << "Missing or invalid argument" << endl; return false; }
        return true;
    };
    switch (it->second) {

        //Array (M)
    case Cmd::MPUSH: {
        if (!needstr(v)) return 1;
        arr(name).PushBack(v);
        break;
    }
    case Cmd::MINS: {
        if (!need(idx) || !needstr(v)) return 1;
        arr(name).Insert(idx, v);
        break;
    }
    case Cmd::MGET: {
        if (!need(idx)) return 1;
        MyArray& a = arr(name);
        if (idx < 0 || idx >= a.Length()) cout << "Out of range" << endl;
        else cout << a.Get(idx) << endl;
        break;
    }
    case Cmd::MDEL: {
        if (!need(idx)) return 1;
        MyArray& a = arr(name);
        if (idx < 0 || idx >= a.Length()) cout << "Out of range" << endl;
        else cout << a.PopIndex(idx) << endl;
        break;
    }
    case Cmd::MSET:
        if (!need(idx) || !needstr(v)) return 1;
        arr(name).Set(idx, v);
        break;
    case Cmd::MLEN: {
        cout << arr(name).Length() << endl;
        break;
    }
        //Single linked list (F)
    case Cmd::FPUSH:{
        if (!needstr(v)) return 1;
        Node::PushBack(flists[name], v);
        break;
    }
    case Cmd::FPUSHFRONT:{
        if (!needstr(v)) return 1;
        Node::PushFront(flists[name], v);
        break;
    }
    case Cmd::FINSBEFORE: {
        if (!needstr(target) || !needstr(v)) return 1;
        Node::InsertBefore(flists[name], target, v);
        break;
    }
    case Cmd::FINSAFTER: {
        if (!needstr(target) || !needstr(v)) return 1;
        Node::InsertAfter(flists[name], target, v);
        break;
    }
    case Cmd::FDEL: {
        if (!needstr(v)) return 1;
        Node::RemoveValue(flists[name], v);
        break;
    }
    case Cmd::FDELFRONT: {
        Node::RemoveFront(flists[name]);
        break;
    }
    case Cmd::FDELBACK: {
        Node::RemoveBack(flists[name]);
        break;
    }
    case Cmd::FDELBEFORE: {
        if (!needstr(target)) return 1;
        Node::RemoveBefore(flists[name], target);
        break;
    }
    case Cmd::FDELAFTER: {
        if (!needstr(target)) return 1;
        Node::RemoveAfter(flists[name], target);
        break;
    }
    case Cmd::FFIND: {
        if (!needstr(v)) return 1;
        cout << (Node::SearchValue(flists[name], v) ? "TRUE" : "FALSE") << endl;
        break;
    }
    case Cmd::FGET: {
        Node::PrintIter(flists[name]);
        break;
    }
    case Cmd::FGETREC: {
        Node::PrintRecur(flists[name]);
        break;
    }

        //Double linked list (L)
    case Cmd::LPUSH: {
        if (!needstr(v)) return 1;
        dbNode::PushBack(llists[name], v);
        break;
    }
    case Cmd::LPUSHFRONT: {
        if (!needstr(v)) return 1;
        dbNode::PushFront(llists[name], v);
        break;
    }
    case Cmd::LINSBEFORE: {
        if (!needstr(target) || !needstr(v)) return 1;
        dbNode::InsertBefore(llists[name], target, v);
        break;
    }
    case Cmd::LINSAFTER: {
        if (!needstr(target) || !needstr(v)) return 1;
        dbNode::InsertAfter(llists[name], target, v);
        break;
    }
    case Cmd::LDEL: {
        if (!needstr(v)) return 1;
        dbNode::RemoveValue(llists[name], v);
        break;
    }
    case Cmd::LDELFRONT: {
        dbNode::RemoveFront(llists[name]);
        break;
    }
    case Cmd::LDELBACK: {
        dbNode::RemoveBack(llists[name]);
        break;
    }
    case Cmd::LDELBEFORE: {
        if (!needstr(target)) return 1;
        dbNode::RemoveBefore(llists[name], target);
        break;
    }
    case Cmd::LDELAFTER: {
        if (!needstr(target)) return 1;
        dbNode::RemoveAfter(llists[name], target);
        break;
    }
    case Cmd::LFIND: {
        if (!needstr(v)) return 1;
        cout << (dbNode::SearchValue(llists[name], v) ? "TRUE" : "FALSE") << endl;
        break;
    }
    case Cmd::LGET: {
        dbNode::PrintIter(llists[name]);
        break;
    }
    case Cmd::LGETBACK: {
        dbNode::PrintBack(llists[name]);
        break;
    }

        //Queue (Q)
    case Cmd::QPUSH: {
        if (!needstr(v)) return 1;
        que(name).push(v);
        break;
    }
    case Cmd::QGET: {
        if (que(name).IsEmpty()) cout << "Empty" << endl;
        else que(name).Print();
        break;
    }
    case Cmd::QPOP: {
        if (que(name).IsEmpty()) cout << "Underflow" << endl;
        else cout << que(name).pop() << endl;
        break;
    }
    case Cmd::QFRONT: {
        if (que(name).IsEmpty()) cout << "Empty" << endl;
        else cout << que(name).frontElem() << endl;
        break;
    }
    case Cmd::QREAR: {
        if (que(name).IsEmpty()) cout << "Empty" << endl;
        else cout << que(name).rearElem() << endl;
        break;
    }

        //Stack (S)
    case Cmd::SPUSH: {
        if (!needstr(v)) return 1;
        stk(name).Push(v);
        break;
    }
    case Cmd::SGET: {
        if (stk(name).IsEmpty()) cout << "Empty" << endl;
        else stk(name).Print();
        break;
    }
    case Cmd::SPOP: {
        if (stk(name).IsEmpty()) cout << "Underflow" << endl;
        else cout << stk(name).Pop() << endl;
        break;
    }
    case Cmd::STOP: {
        if (stk(name).IsEmpty()) cout << "Empty" << endl;
        else cout << stk(name).Top() << endl;
        break;
    }

        //Tree (T) Complete Binary Tree
    case Cmd::TINSERT: {
        if (!need(num)) return 1;
        trees[name] = btNode::InsertNode(trees[name], num);
        break;
    }
    case Cmd::TGET: {  // и ISMEMBER
        if (!need(num)) return 1;
        cout << (btNode::searchNode(trees[name], num) ? "TRUE" : "FALSE") << endl;
        break;
    }
    case Cmd::TISCOMPLETE: {
        cout << (btNode::isComplete(trees[name]) ? "TRUE" : "FALSE") << endl;
        break;
    }
    case Cmd::TBFS: {
        PrintVector(toString(btNode::bfs(trees[name])));
        break;
    }
    case Cmd::TDFS: {
        vector<int> r;
        btNode::dfs(trees[name], r);
        PrintVector(toString(r));
        break;
    }case Cmd::TINORDER: {
        if (!trees[name]) cout << "Empty";
        btNode::inOrder(trees[name]);
        cout << endl;
        break;
    }case Cmd::PRINT: {
        if (arrays.count(name)) arr(name).Print();
        else if (stacks.count(name)) stk(name).Print();
        else if (queues.count(name)) que(name).Print();
        else if (flists.count(name)) Node::PrintIter(flists[name]);
        else if (llists.count(name)) dbNode::PrintIter(llists[name]);
        else if (trees.count(name)) PrintVector(toString(btNode::bfs(trees[name])));
        else {cout << "Structure not found" << endl; return 1;}
        break;
    }
                      }
    
    return 0;
}