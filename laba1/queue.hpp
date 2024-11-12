#include "header.h"

struct QueueNode {
    std::string data;
    QueueNode* next;

    QueueNode(std::string value) : data(value), next(nullptr) {}
};

struct Queue{
    QueueNode* head;
    QueueNode* tail;
    Queue(){
        head = nullptr;
        tail = nullptr;
        loadFromFile("queue.data");
    }
    void push(std::string value); //добавление
    void pop(); //удаление
    void display(); //вывод на экран
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

void Queue::push(std::string value){
    QueueNode* newNode = new QueueNode(value);
    if (head == nullptr){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode; //устанавливаем указатель текущего хвоста на новый узел
        tail = newNode;
    }
    saveToFile("queue.data"); // сохраняем состояние очереди после добавления
}

void Queue::pop(){
    if(head == nullptr){
        cout << "Queue is empty" << endl;
    } else {
        QueueNode* temp = head;
        head = head->next; //удаляем первый элемент очереди
        delete temp;
        if (head == nullptr){ //если очередь пуста, то голова и конец = nullptr
            tail = nullptr;
        }
        saveToFile("queue.data"); // сохраняем состояние очереди после добавления
    }
}
    
void Queue::display(){
    if (head == nullptr){
        cout << "Queue is empty" << endl;
    } else {
        QueueNode* current = head;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

// Сохранение очереди в файл
void Queue::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        cout << "Cannot open file for writing: " << filename << endl;
        return;
    }
    QueueNode* current = head;
    while (current != nullptr) {
        file << current->data << endl;
        current = current->next;
    }
    file.close();
}

// Загрузка очереди из файла
void Queue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }
    std::string value;
    while (std::getline(file, value)) {
        push(value);
    }
    file.close();
}
