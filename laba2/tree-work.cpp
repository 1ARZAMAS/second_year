#include <iostream>
#include <string>
#include <sstream>
#include "binary-tree.hpp"

using namespace std;

BinaryTree<int> tree;

int main() {
    string command;
    while(true){
        cout << "< ";
        getline(cin, command);
        istringstream iss(command);
        iss >> command;
        if (command == "exit"){
            return 0;
        } else if (command == "TPUSH"){ // добавление элемента в конец
            int value;
            iss >> value;
            tree.insertWithDepth(value);
            cout << endl;
        } else if (command == "TEST"){
            tree.insertWithDepth(7);
            tree.insertWithDepth(3);
            tree.insertWithDepth(2);
            tree.insertWithDepth(1);
            tree.insertWithDepth(9);
            tree.insertWithDepth(5);
            tree.insertWithDepth(4);
            tree.insertWithDepth(6);
            tree.insertWithDepth(8);
            tree.insertWithDepth(0);
            cout << endl;
        } else {
            cout << "incorrect command" << endl;
        }
    }
    return 0;
}
