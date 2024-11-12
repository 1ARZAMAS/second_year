#include "header.h"

#include "array.hpp"
#include "double-linked-list.hpp"
#include "hash-table.hpp"
#include "linked-list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tree.hpp"

CustomArray customArray(10); // создание массива
LinkedList linkedList; // создание односвзяного листа
DoubleLinkedList doubleLinkedList; // создание двусвязного листа
Queue queue; // создание очереди
Stack stack; // создание стэка
AVLTree tree; // создание дерева
HashTable hash_table = HashTable(); // создание хэш-таблицы

void processQuery(const std::string& query) {
    std::stringstream ss(query);
    std::string command;
    ss >> command;
    // ----------ARRAY------
    if (command == "APUSH"){ // добавление элемента в конец
        std::string value;
        ss >> value;
        customArray.addToTheEnd(value);
    }
     else if (command == "AINSERT") { // добавление элемента по индексу 
        int index;
        std::string value;
        ss >> index >> value;
        customArray.add(index, value);
    }
    else if (command == "APOP") { // удаление элемента по индексу
        int index;
        ss >> index;
        customArray.remove(index);
    }
    else if (command == "AREPLACE") { // замена элемента по индексу
        int index;
        std::string value;
        ss >>  index >> value;
        customArray.replace(index, value);
    }
    else if (command == "ALENGTH") { // длина массива
        customArray.length();
    }
    else if (command == "AGET") { // получение элемента по индексу
        int index;
        ss >> index;
        customArray.get(index);
    }
    else if (command == "AREAD") { // чтение
        customArray.display();
    }

    // ----------DLLIST-------
    else if (command == "DLPUSH_HEAD"){ // добавление элемента в голову!!!!!!!!!!!!!!!!!!!!!!!!!!! убежище завершил мне программу после этой команды >:(
        std::string value;
        ss >> value;
        doubleLinkedList.addToTheHead(value);
    }
    else if (command == "DLPUSH_TAIL"){ // добавление элемента в хвост
        std::string value;
        ss >> value;
        doubleLinkedList.addToTheEnd(value);
    }
    else if (command == "DLPOP_HEAD"){ // удаление элемента с головы !!!!!!!!!!!!!!!!!!!!!!!!!!! убежище завершил мне программу после этой команды >:(
        doubleLinkedList.removeFromTheHead();
    }
    else if (command == "DLPOP_TAIL"){ // удаление элемента с хвоста
        doubleLinkedList.removeFromTheEnd();
    }
    else if (command == "DLPOP_VALUE"){ // удаление элемента по значению
        std::string value;
        ss >> value;
        doubleLinkedList.removeByValue(value);
    }
    else if (command == "DLSEARCH"){ // поиск элемента по значению
        std::string value;
        ss >> value;
        doubleLinkedList.searchByValue(value);
    }
    else if (command == "DLREAD"){ // чтение
        doubleLinkedList.display();
    }

    // ----------LIST-------
    else if (command == "LPUSH_HEAD"){ // добавление элемента в голову
        std::string value;
        ss >> value;
        linkedList.addToTheHead(value);
    }
    else if (command == "LPUSH_TAIL"){ // добавление элемента в хвост
        std::string value;
        ss >> value;
        linkedList.addToTheEnd(value);
    }
    else if (command == "LPOP_HEAD"){ // удаление элемента с головы !!!!!!!!!!!!!!!!!!!!!!!!!!! убежище завершил мне программу после этой команды >:(
        linkedList.removeFromTheHead();
    }
    else if (command == "LPOP_TAIL"){ // удаление элемента с хвоста
        linkedList.removeFromTheEnd();
    }
    else if (command == "LPOP_VALUE"){ // удаление элемента по значению
        std::string value;
        ss >> value;
        linkedList.removeByValue(value);
    }
    else if (command == "LSEARCH"){ // поиск элемента по значению
        std::string value;
        ss >> value;
        linkedList.searchByValue(value);
    }
    else if (command == "LREAD"){ // чтение
        linkedList.display();
    }

    // ----------QUEUE-------
    else if (command == "QPUSH"){ // Добавление элемента
        std::string value;
        ss >> value;
        queue.push(value);
    }
    else if (command == "QPOP"){ // удаление элемента
        queue.pop();
    }
    else if (command == "QREAD"){ //вывод на экран
        queue.display();
    }
    
    // ----------STACK-------
    else if (command == "SPUSH"){ // Добавление элемента
        std::string item;
        ss >> item;
        stack.push(item);
    }
    else if (command == "SPOP"){ // удаление элемента
        stack.pop();
    }
    else if (command == "SREAD"){ //вывод на экран
        stack.display();
    }

    // ----------HASH-TABLE------- ДОДЕЛАТЬ НАДО ЕТИТЬ КОЛОТИТЬ
    else if (command == "HPUSH"){ // Добавление элемента
        std::string key;
        std::string value;
        ss >> key >> value;
        hash_table.push(key, value);
    }
    else if (command == "HPOP"){ // Удаление элемента
        std::string key;
        ss >> key;
        hash_table.pop(key);
    }
    else if (command == "HGET"){ // Получение значения по ключу
        std::string key;
        ss >> key;
        hash_table.get(key);
    }

    // ----------TREE-------
    else if (command == "TPUSH"){ // Добавление элемента
        std::string value;
        ss >> value;
        //tree.root = tree.insert(tree.root, value); 
        tree.insert(value); 
    }
    else if (command == "TSEARCH"){ // Поиск элемента по дереву
        std::string value;
        ss >> value;
        cout << (tree.search(tree.root, value) ? "Found" : "Not Found") << endl; 
    }
    else if (command == "TPOP"){ // удаление элемента
        std::string value;
        ss >> value;
        //tree.root = tree.remove(tree.root, value); 
        tree.remove(value); 
    }
    else if (command == "TREAD"){ // Вывод на экран
        tree.inOrder(tree.root);
        cout << endl;
    } 
    else if (command == "PRINT"){ // вывод на экран всех структур
        customArray.display();
        doubleLinkedList.display();
        linkedList.display();
        queue.display();
        stack.display();
        tree.inOrder(tree.root);
        cout << endl;
    } 
    else {
        cout << "Unknown command" << endl;
    }
}