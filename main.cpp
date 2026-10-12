#include <iostream>
#include <string>
#include "FileInOut.h"
using namespace std;
int main(int argc, char* argv[]) {
    string file;
    string query;
    for (int i = 1; i < argc; i++) {
        string a =argv[i];
        if (a == "--file" && i + 1 < argc)  file = argv[++i];
        else if (a == "--query" && i+ 1 < argc)  query = argv[++i];
    } if (file.empty() ||query.empty()) {
        cerr << "Usage ./ds --file file.data --query 'COMAND name [args]'" << endl;
        return 1;
    }
    FileInOut fio;
    fio.Load(file);
    int rtrn = fio.Execute(query);
    if (rtrn == 0) fio.Save(file);
    return rtrn;
}
