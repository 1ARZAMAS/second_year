#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data; // значение узла
    Node* left; // указатель на левое поддерево
    Node* right; // указатель на правое поддерево
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
struct BinaryTree {
    Node<T>* root; // указатель на корень дерева

    BinaryTree() : root(nullptr) {}

    // Функция для создания узла
    Node<T>* createNode(const T& data) {
        return new Node(data);
    }

    // Функция для вставки узла и вывода его глубины
    void insertWithDepth(const T& key);
    // Рекурсивная вставка элемента и вывод глубины
    void insertWithDepthHelper(Node<T>* node, const T& key, int depth);
    bool search(Node<T>* node, const T& key);// Поиск узла в дереве
    bool search(const T& key);
    void inOrder(Node<T>* node);// Симметричный обход дерева
    void inOrder();
    void clear(Node<T>* node);// Очистка дерева
    void clear();
};

template <typename T>
void BinaryTree<T>::insertWithDepth(const T& key) {
    if (key == 0) { // Если значение 0, пропускаем его
        return;
    }
    if (root == nullptr) {
        root = createNode(key);
        cout << 1 << " "; // Глубина для первого элемента всегда 1
    } else {
        insertWithDepthHelper(root, key, 1);
    }
}

// Рекурсивная вставка элемента и вывод глубины
template <typename T>
void BinaryTree<T>::insertWithDepthHelper(Node<T>* node, const T& key, int depth) {
    if (key < node->data) {
        if (node->left == nullptr) {
            node->left = createNode(key);
            cout << depth + 1 << " "; // Глубина = текущая глубина + 1
        } else {
            insertWithDepthHelper(node->left, key, depth + 1);
        }
    } else if (key > node->data) {
        if (node->right == nullptr) {
            node->right = createNode(key);
            cout << depth + 1 << " "; // Глубина = текущая глубина + 1
        } else {
            insertWithDepthHelper(node->right, key, depth + 1);
        }
    }
    // Если элемент уже существует, не делаем вставку и ничего не выводим
}

// Поиск узла в дереве
template <typename T>
bool BinaryTree<T>::search(Node<T>* node, const T& key) {
    if (node == nullptr) {
        return false;
    }
    if (key == node->data) {
        return true;
    } else if (key < node->data) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

template <typename T>
bool BinaryTree<T>::search(const T& key) {
    return search(root, key);
}

// Симметричный обход дерева
template <typename T>
void BinaryTree<T>::inOrder(Node<T>* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}

template <typename T>
void BinaryTree<T>::inOrder() {
    if (root != nullptr) {
        inOrder(root);
        cout << endl;
    } else {
        cout << "Tree is empty" << endl;
    }
}

// Очистка дерева
template <typename T>
void BinaryTree<T>::clear(Node<T>* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
void BinaryTree<T>::clear() {
    clear(root);
    root = nullptr;
}