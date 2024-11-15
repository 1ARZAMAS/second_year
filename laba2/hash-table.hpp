#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int SIZE = 500;

template <typename T>
struct HashTableItem {
    T data; // Только значение
    HashTableItem* next; // Указатель на следующий элемент
};

template <typename T>
struct HashTable {
    HashTableItem<T>* items[SIZE]; // Массив указателей на элементы хеш-таблицы
    int count; // Количество элементов

    HashTable() : count(0) {
        for (int i = 0; i < SIZE; i++) {
            items[i] = nullptr; // Инициализируем таблицу пустыми указателями
        }
    }

    int HashFun(const T& data); // Хеш-функция
    HashTableItem<T>* createItem(const T& data); // Создание элемента
    void push(const T& data); // Добавление элемента
    void pop(const T& data); // Удаление элемента
    void get(const T& data); // Проверка наличия элемента
    void clear(); // Очистка таблицы
};

template <typename T>
int HashTable<T>::HashFun(const T& data) {
    const int prime = 43; // Простое число для улучшения хеширования
    int hash = 0;
    for (char letter : data) {
        hash = (hash * prime + static_cast<int>(letter)) % SIZE; // Хэшируем через ASCII код
    }
    return hash;
}

template <typename T>
HashTableItem<T>* HashTable<T>::createItem(const T& data) {
    return new HashTableItem<T>{ data, nullptr };
}

template <typename T>
void HashTable<T>::push(const T& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem<T>* item = createItem(data);

    if (items[index] == nullptr) {
        items[index] = item; // Вставляем элемент в пустую ячейку
        count++;
    } else {
        HashTableItem<T>* current = items[index];
        // Проверяем, есть ли уже такое значение
        while (current != nullptr) {
            if (current->data == data) {
                // Если значение уже есть, ничего не делаем
                delete item;
                return;
            }
            current = current->next;
        }
        // Если значение уникально, добавляем его в конец цепочки
        item->next = items[index];
        items[index] = item;
        count++;
    }
}

template <typename T>
void HashTable<T>::pop(const T& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem<T>* current = items[index];
    HashTableItem<T>* prev = nullptr;

    while (current != nullptr) {
        if (current->data == data) {
            if (prev == nullptr) {
                items[index] = current->next; // Удаляем первый элемент в цепочке
            } else {
                prev->next = current->next; // Удаляем элемент, указывая на следующий
            }
            delete current;
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "This value is not in the table" << endl; // Если элемент не найден
}

template <typename T>
void HashTable<T>::get(const T& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem<T>* current = items[index];

    while (current != nullptr) {
        if (current->data == data) {
            cout << "Element " << data << " is in the table" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Element " << data << " is not in the table" << endl;
}

template <typename T>
void HashTable<T>::clear() {
    for (int i = 0; i < SIZE; ++i) {
        HashTableItem<T>* current = items[i];
        while (current != nullptr) {
            HashTableItem<T>* temp = current;
            current = current->next;
            delete temp; // Удаление элемента
        }
        items[i] = nullptr;
    }
    count = 0;
}