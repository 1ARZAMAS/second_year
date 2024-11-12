#include "header.h"

struct DLLNode {
    std::string data;
    DLLNode* next;
    DLLNode* prev;

    DLLNode(std::string value) : data(value), next(nullptr), prev(nullptr) {}
};

struct DoubleLinkedList{ //done
    std::string* doubleLinkedList; 
    DLLNode* head;
    DLLNode* tail;

    DoubleLinkedList() : head(nullptr), tail(nullptr) {
        loadFromFile("DLList.data"); // загружаем данные из файла при создании объекта
    }

    void addToTheHead(std::string value); // добавление элемента в голову
    void addToTheEnd(std::string value); // добавление элемента в хвост
    void removeFromTheHead(); // удаление элемента с головы
    void removeFromTheEnd(); // удаление элемента с хвоста
    void removeByValue(std::string value); // удаление элемента по значению
    bool searchByValue(std::string value); // поиск элемента по значению
    void display();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void clear();
};

void DoubleLinkedList::clear() {
    while (head != nullptr) {
        removeFromTheHead();
    }
}

void DoubleLinkedList::addToTheHead(std::string value){ // добавление в самое начало
    DLLNode* newNode = new DLLNode(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    saveToFile("DLList.data"); // сохраняем изменения в файл
}

void DoubleLinkedList::addToTheEnd(std::string value){
    DLLNode* newNode = new DLLNode(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    saveToFile("DLList.data"); // сохраняем изменения в файл
}

void DoubleLinkedList::removeFromTheHead(){// удаление элемента с головы
    if (head == nullptr){
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    } else {
        DLLNode* temp = head;
        head->next->prev = nullptr;
        head = head->next; //удаляем первый элемент
        delete temp;
    }
    saveToFile("DLList.data"); // Сохраняем изменения в файл
}

void DoubleLinkedList::removeFromTheEnd(){ // удаление элемента с хвоста
    if (head == nullptr){
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    }
    if (head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    DLLNode* current = tail;
    tail->prev->next = nullptr;
    tail = tail->prev; // удаляем последний элемент
    delete current;
    saveToFile("DLList.data"); // сохраняем изменения в файл
}

void DoubleLinkedList::removeByValue(std::string value){ // удаление элемента по значению
    if (head == nullptr){
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    }
    if (value == head->data){
        removeFromTheHead();
        return;
    }
    if (value == tail->data){
        removeFromTheEnd();
        return;
    }
    
    DLLNode* current = head;
    while (current->next && current->next->data != value){ // пока вообще можем идти по списку
    // и пока значение не будет равно нужному
        current = current->next;
    }
    if (current->next == nullptr){
        cout << "This value is not in the list" << endl;
        return;
    }

    if (current->prev){ // если существует предудущий узел, то мы указываем предыдущему
        current->prev->next = current->next; // указывать на следующий текущему
    } else { // если это голова, те предыдущего узла нет, то обновляем, чтобы голова 
        head = current->next; // указывала на следующий узел
    }

    if (current->next){ // если существует следующий узел, то мы указываем чтобы следующий
        current->next->prev = current->prev; // указывал на предыдущий текущему
    } else { // если это хвост, то следующего нет, то обновляем, чтобы он указывал на предыдущий
        tail = current->prev;
    }
    delete current; // и удаляем текущий
    saveToFile("DLList.data"); // Сохраняем изменения в файл
}

bool DoubleLinkedList::searchByValue(std::string value) {
    DLLNode* current = head;
    while (current) {
        if (current->data == value) {
            std::cout << "Value " << current->data << " is in the list" << std::endl;
            return true;
        }
        current = current->next;
    }
    std::cout << "There is no " << value << " in the list" << std::endl;
    return false;
}

void DoubleLinkedList::display(){
    DLLNode* current = head;
    if (current == nullptr){
        cout << "Doubly linked list is empty" << endl;
    } else {
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
}

void DoubleLinkedList::loadFromFile(const std::string& filename) { // загрузка данных из файла
    clear(); // очищаем текущий лист
    std::ifstream file(filename);
    if (!file) {
        cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        addToTheEnd(line); // добавляем элементы
    }
    file.close();
}

void DoubleLinkedList::saveToFile(const std::string& filename) { // сохранение в файл
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }

    DLLNode* current = head;
    while (current) {
        file << current->data << std::endl; // записываем данные в файл
        current = current->next;
    }
    file.close();
}