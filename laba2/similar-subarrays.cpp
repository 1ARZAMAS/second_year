#include <iostream>
#include <string>
#include <sstream>
#include "array.hpp"

using namespace std;

CustomArray<int> customArray(10);

void similarSubArrays(CustomArray<int>& customArray){
    int total_sum = 0;
    for (int i = 0; i < customArray.size; i++){
        total_sum += customArray[i];
    }
    CustomArray<int> firstArray(10);
    CustomArray<int> secondArray(10);
    int sumArray1 = 0, sumArray2 = 0;
    for (int i = 0; i < customArray.size; i++){ // Если во сумма второго подмассива больше(=) или сумма второго подмассива больше(=),
        if (sumArray1 <= sumArray2 || sumArray2 >= (total_sum / 2)){ // чем половина суммы изначального массива, то 
            firstArray.addToTheEnd(customArray[i]); // добавим значение в первый подмассив
            sumArray1 += customArray[i]; // и добавим в сумму подмассива
        } else {
            secondArray.addToTheEnd(customArray[i]); // и наоборот
            sumArray2 += customArray[i];
        }
    }
    cout << "Sum first subarray: " << sumArray1 << " and the array is: ";
    firstArray.display();
    cout << "\nSum second subarray: " << sumArray2 << " and the array is: ";
    secondArray.display();
}

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
                int value;
                iss >> value;
                if (value <= 0){
                    cerr << "The number must be natural" << endl;
                }
                if (!customArray.isExist(value)){
                    customArray.addToTheEnd(value);
                }
            } catch (const exception& ErrorInfo) {
                cerr << ErrorInfo.what() << endl;
            }
        } else if (wordFromQuery == "TEST"){ //
            try {
                customArray.addToTheEnd(5);
                customArray.addToTheEnd(8);
                customArray.addToTheEnd(1);
                customArray.addToTheEnd(14);
                customArray.addToTheEnd(7);
            } catch (const exception& ErrorInfo) {
                cerr << ErrorInfo.what() << endl;
            }
        } else if (wordFromQuery == "SIMILAR"){ // 
            try {
                customArray.shellSort();
                customArray.display();
                similarSubArrays(customArray);
            } catch (const exception& error) {
                cerr << error.what() << endl;
            }
        } else if (wordFromQuery == "DISPLAY"){
            customArray.display();
        } else {
            cerr << "Incorrect query" << endl;
        }
    }
}
