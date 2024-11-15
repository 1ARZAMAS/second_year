#include <iostream>
#include <string>
#include <sstream>
#include "array.hpp"

using namespace std;

CustomArray<string> romanNumerals(13);
CustomArray<int> values(13);

string intToRoman(int num) {
    // Массивы для римских чисел и их значений
    romanNumerals.initialize({"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"});
    values.initialize({1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1});

    string result = "";
    
    for (int i = 0; i < 13; ++i) { // пройдемся по всем числам из списка
        while (num >= values[i]) {// если число больше текущего значения из списка, то 
            result += romanNumerals[i]; // добавляем римскую цифру в результат
            num -= values[i]; // уменьшаем число на соответствующее значение
        }
    }

    return result;
}

int main() {
    int num;
    cin >> num;
    cout << intToRoman(num);
    return 0;
}
