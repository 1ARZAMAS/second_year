#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct StackNode {
    T data;
    StackNode* next;

    StackNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
struct Stack {
    StackNode<T>* top;
    Stack(){
        top = nullptr;
    }
    void clear();
    void push(T value); //добавление
    void pop(); //удаление
    void display(); //вывод стека
    bool empty();
    T Top();
};

template <typename T>
void Stack<T>::clear(){
    while (top != nullptr) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(T value){
    StackNode<T>* node = new StackNode(value);
    if (top == nullptr){ // если стек пустой
        top = node; // то top = введеное значение
    } else {
        node->next = top; // если стек не пустой, то тогда предыдущая top 
        top = node; // станет 2м значением, новое значение = top
    }
}

template <typename T>
void Stack<T>::pop(){
    if (top == nullptr){
        cout << "Stack is empty, value cannot be deleted" << endl;
    } else {
        StackNode<T>* temp = top; // новая переменная, которая указывает на топ
        top = top->next; // перезаписываем
        delete temp; // и удаляем перменную
    }
}

template <typename T>
void Stack<T>::display(){
    if (top == nullptr){
        cout << "Stack is empty" << endl;
    } else {
        StackNode<T>* current = top;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

template <typename T>
bool Stack<T>::empty(){
    if (top == nullptr){
        return true;
    } else {
        return false;
    }
}

template <typename T>
T Stack<T>::Top() {
    if (this->top == nullptr) {
        throw std::runtime_error("Stack is empty!");
    }
    return this->top->data;
}
