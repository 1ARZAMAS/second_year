#include <iostream>
#include <string>
#include <sstream>
#include "array.hpp"

using namespace std;
CustomArray<int> customArray(10);

void subarray (int targetSum) {
    for (int i = 0; i < customArray.size; ++i) {
        int currentSum = 0;
        for (int j = i; j < customArray.size; ++j) {
            currentSum += customArray[j];
            if (currentSum == targetSum) {
                for (int k = i; k <= j; ++k) {// Выводим подмассив
                    cout << customArray[k] << " ";
                }
                cout << endl;
            }
        }
    }
}

int main(){
    string command;
    while(true){
        cout << "< ";
        getline(cin, command);
        istringstream iss(command);
        iss >> command;
        if (command == "exit"){
            return 0;
        } else if (command == "APUSH"){ // добавление элемента в конец
            int value;
            iss >> value;
            customArray.addToTheEnd(value);
        } else if (command == "TEST"){
            customArray.initialize({4,-7, 1, 5, -4, 0, -3, 2, 4, 1});
        } else if (command == "subarray"){
            int targetSum = 5;
            subarray(targetSum);
        } else {
            cout << "incorrect command" << endl;
        }
    }
}