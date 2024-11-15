#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
#include "stack.hpp"

using namespace std;

// Функция для определения приоритета оператора
int prec(char c) {
    if (c == '/' || c == '*'){
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return -1;
    }
}

string infixToPostfix(string& line) {
    Stack<char> st;  // используем стек для символов
    string result;
    int i = 0;

    while (i < line.length()) {
        char c = line[i];

        if (isdigit(c)) {// если это цифра, соберем все символы в число
            while (i < line.length() && isdigit(line[i])) {
                result += line[i];
                i++;
            }
            result += ' '; // разделяем числа
        }
        else if (c == '(') {
            st.push(c);  // push открывающую скобку
            i++;
        }
        else if (c == ')') { //Пока на верхушке стека не окажется открывающая скобка,
            // выталкиваем операторы в результат
            while (!st.empty() && st.Top() != '(') {
                result += st.Top();
                st.pop();
                result += ' ';  // разделяем операторы
            }
            st.pop();  // убираем из стека (
            i++;
        }
        else {
            // выталкиваем операторы с более высоким или равным приоритетом
            while (!st.empty() && prec(c) <= prec(st.Top())) {
                result += st.Top();
                st.pop();
                result += ' ';  // разделяем операторы
            }
            st.push(c);  // push текущий оператор в стек
            i++;
        }
    }

    // выталкиваем оставшиеся операторы из стека в результат
    while (!st.empty()) {
        result += st.Top();
        st.pop();
        result += ' ';  // разделяем операторы
    }

    return result;
}


int RPN(string line) {
    Stack<int> values;
    istringstream tokens(line);
    string token;
    
    while (tokens >> token) {
        if (isdigit(token[0])) {
            // Если токен — это число, добавляем его в стек
            values.push(stoi(token));
        }
        else {
            // Если токен — это оператор, извлекаем два числа из стека
            if (values.empty()) {
                cout << "Error: insufficient values in stack." << endl;
                return -1;
            }
            int a = values.Top(); values.pop();
            if (values.empty()) {
                cout << "Error: insufficient values in stack." << endl;
                return -1;
            }
            int b = values.Top(); values.pop();
            int result = 0;

            switch (token[0]) {
                case '+': 
                    result = a + b; 
                    break;
                case '-': 
                    result = a - b; 
                    break;
                case '*': 
                    result = a * b; 
                    break;
                case '/': 
                    if (b == 0) {
                        cout << "Error: division by zero." << endl;
                        return -1;
                    }
                    result = a / b; 
                    break;
                default: 
                    cout << "Invalid operator: " << token[0] << endl; 
                    return -1;
            }

            // помещаем результат обратно в стек
            values.push(result);
        }
    }
    StackNode<int>* current = values.top;
    if (current->next == nullptr){// в стеке должно остаться только одно число — это результат
        return values.Top();
    }
}

int main() {
    string line;
    cin >> line;
    string result = infixToPostfix(line); // преобразование инфиксной записи в постфиксную
    cout << RPN(result);
    return 0;
}
