#include <iostream>
#include <string>
#include <sstream>
#include "hash-table.hpp"

using namespace std;

HashTable hash_table = HashTable<string>(); // создание хэш-таблицы

int main(){
    string command;
    while(true){
        cout << "< ";
        getline(cin, command);
        istringstream iss(command);
        string wordFromQuery;
        iss >> wordFromQuery; // первое слово в команде
         
        if (wordFromQuery == "exit"){
            return 0;
        } else if (wordFromQuery == "SETADD"){ // SETADD - добавление
            try {
                string value;
                iss >> value;
                hash_table.push(value);
            } catch (const exception& ErrorInfo) {
                cerr << ErrorInfo.what() << endl;
            }
        } else if (wordFromQuery == "SETDEL"){ // SETDEL - удаление
            try {
                string value;
                iss >> value;
                hash_table.pop(value);

            } catch (const exception& ErrorInfo) {
                cerr << ErrorInfo.what() << endl;
            }
        } else if (wordFromQuery == "SET_AT"){ // SET_AT - проверка есть ли в множестве
            try {
                string value;
                iss >> value;
                hash_table.get(value);
            } catch (const exception& error) {
                cerr << error.what() << endl;
            }
        //} else if (wordFromQuery == "DISPLAY"){
        //    hash_table.
        } else {
            cerr << "Incorrect query" << endl;
        }
    }
}
