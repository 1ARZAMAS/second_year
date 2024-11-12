#include "header.h"

struct StackNode {
    std::string data;
    StackNode* next;

    StackNode(std::string value) : data(value), next(nullptr) {}
};

struct Stack {
    StackNode* top;
    Stack(){
        top = nullptr;
        loadFromFile("stack.data");
    }
    
    void clear();
    void push(std::string value); //добавление
    void pop(); //удаление
    void display(); //вывод стека
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

void Stack::clear(){
    while (top != nullptr) {
        pop();
    }
}

void Stack::push(std::string value){
    StackNode* node = new StackNode(value);
    if (top == nullptr){ // если стек пустой
        top = node; // то top = введеное значение
    } else {
        node->next = top; // если стек не пустой, то тогда предыдущая top 
        top = node; // станет 2м значением, новое значение = top
    }
    saveToFile("stack.data"); // Сохраняем состояние стека после добавления
}

void Stack::pop(){
    if (top == nullptr){
        cout << "Stack is empty, value cannot be deleted" << endl;
    } else {
        StackNode* temp = top; // новая переменная, которая указывает на топ
        top = top->next; // перезаписываем
        delete temp; // и удаляем перменную
        saveToFile("stack.data"); // Сохраняем состояние стека после добавления
    }
}
    
void Stack::display(){
    if (top == nullptr){
        cout << "Stack is empty" << endl;
    } else {
        StackNode* current = top;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

void Stack::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        cout << "Cannot open file for writing: " << filename << endl;
        return;
    }
    StackNode* current = top;
    while (current != nullptr) {
        file << current->data << endl;
        current = current->next;
    }
    file.close();
}

// Загрузка стека из файла
void Stack::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        cout << "Cannot open file for reading: " << filename << endl;
        return;
    }
    std::string value;
    clear();  // Сбрасываем текущий стек перед загрузкой
    while (std::getline(file, value)) {
        push(value);
    }
    file.close();
}
