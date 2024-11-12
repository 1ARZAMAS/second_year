#include "header.h"

struct LLNode {
    std::string data;
    LLNode* next;

    LLNode(std::string value) : data(value), next(nullptr) {}
};

struct LinkedList {
    LLNode* head;

    LinkedList() : head(nullptr) {
        loadFromFile("linkedlist.data"); // загружаем данные из файла при создании объекта
    }

    void addToTheHead(std::string value); // добавим в голову
    void addToTheEnd(std::string value); // добавим в хвост
    void removeFromTheHead(); // удалим с головы
    void removeFromTheEnd(); // удалим с хвоста
    void removeByValue(std::string value); // удалим по значению
    void searchByValue(std::string value); // найдем по значению
    void display(); // вывод на экран
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

void LinkedList::addToTheHead(std::string value) {
    LLNode* newNode = new LLNode(value);
    newNode->next = head; // создадим новую ноду и запишем ее в голову
    head = newNode;
    saveToFile("linkedlist.data"); // сохраняем после добавления
}

void LinkedList::addToTheEnd(std::string value) {
    LLNode* newNode = new LLNode(value);
    if (head == nullptr) { // если список пустой, то добавление в хвост = добавление в голову
        head = newNode;
    } else {
        LLNode* current = head;
        while (current->next != nullptr) { // пройдемся до конца списка
            current = current->next; // и запишем туда значение
        }
        current->next = newNode;
    }
    saveToFile("linkedlist.data"); // сохраняем после добавления
}

void LinkedList::removeFromTheHead() {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    LLNode* temp = head; // создадим временную переменную, которая будет равна голове, 
    head = head->next; // чтоб удаление было корректным
    delete temp;
    saveToFile("linkedlist.data"); // сохраняем после добавления
}

void LinkedList::removeFromTheEnd() {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        saveToFile("linkedlist.data"); // сохраняем после добавления
        return;
    }
    LLNode* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next; // удаляем последний узел
    current->next = nullptr; // обнуляем указатель на последний элемент
    saveToFile("linkedlist.data"); // сохраняем после добавления
}

void LinkedList::removeByValue(std::string value) {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    if (value == head->data) {
        removeFromTheHead();
        return;
    }
    LLNode* current = head;
    while (current->next && current->next->data != value) { // пока можем идти по листу и пока значение не будет равно нужному
        current = current->next;
    }
    if (current->next == nullptr) { // если прошлись, а значение так и не нашли, то его нет вовсе
        std::cout << "This value is not in the list" << std::endl;
        return;
    }
    LLNode* temp = current->next; // новая переменная, чтоб не потерять значение
    current->next = temp->next; // перезаписываем
    delete temp; // и удаляем временную переменную
    saveToFile("linkedlist.data"); // сохраняем после добавления
}

void LinkedList::searchByValue(std::string value) {
    LLNode* current = head;
    while (current != nullptr && current->data != value) { // пока можем идти по листу и пока значение не будет равно нужному
        current = current->next;
    }
    if (current != nullptr) { // если прошлись по листу и остановились где-то, кроме nullptr, то
        std::cout << "Value " << current->data << " is in the list" << std::endl;
    } else {
        std::cout << "There is no " << value << " in the list" << std::endl;
    }
}

void LinkedList::display() {
    LLNode* current = head;
    if (current == nullptr){
        cout << "Linked list is empty" << endl;
    } else {
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

void LinkedList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }
    LLNode* current = head;
    while (current != nullptr) {
        file << current->data << std::endl;
        current = current->next;
    }
}

void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }
    std::string value;
    while (file >> value) {
        addToTheEnd(value);
    }
}
