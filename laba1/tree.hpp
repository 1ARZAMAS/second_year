#include "header.h"

struct AVLNode {
    std::string key; // значение узла
    AVLNode* left; // указатели на левые и правые дочерние узлы
    AVLNode* right;
    int height; // высота узла
    // инициализируем дерево
    AVLNode(std::string value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

struct AVLTree {
    AVLNode* root; // Указатель на корень дерева

    AVLTree() : root(nullptr) {
        loadFromFile("AVLtree.data"); // Загрузка дерева из файла при создании
    }

    void saveNode(AVLNode* node, std::ofstream& file);
    int height(AVLNode* node); // высота узла
    int balanceFactor(AVLNode* node); // вычисляет баланс
    void updateHeight(AVLNode* node); // обновляет высоту дерева на основе дочерних узлов
    AVLNode* rotateRight(AVLNode* y); // правый поворот для балансировки дерева
    AVLNode* rotateLeft(AVLNode* x); // левый поворот для балансировки дерева
    AVLNode* balance(AVLNode* node); // проверяет баланс и выполняет повороты, если нужно
    AVLNode* insert(AVLNode* node, std::string key); // вставляем узел в дерево и балансируем
    AVLNode* minValueNode(AVLNode* node); // находим самый левый узел (минимальное значение)
    AVLNode* remove(AVLNode* node, std::string key); // удаляем узел и балансируем
    bool search(AVLNode* node, std::string key); // проверяем есть ли узел в дереве с нужным значением
    void inOrder(AVLNode* node);
    void inOrder();
    void clear();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    void insert(const std::string& key);
    void remove(const std::string& key);
};

void AVLTree::clear() {
    while (root) {
        root = remove(root, root->key); // Удаляем корень, пока он не станет пустым
    }
}

void AVLTree::saveNode(AVLNode* node, std::ofstream& file) {
    if (node) {
        file << node->key << std::endl; // Сохраняем ключ узла
        AVLTree::saveNode(node->left, file);      // Рекурсивно сохраняем левое поддерево
        AVLTree::saveNode(node->right, file);     // Рекурсивно сохраняем правое поддерево
    }
}

int AVLTree::height(AVLNode* node) { // высота узла
    if (node){// возвращает высоту узла 0, если узел пуст
        return node->height;
    } else {
        return 0;
    }
}

int AVLTree::balanceFactor(AVLNode* node) {// вычисляет баланс
    if (node){
        return height(node->left) - height(node->right);
    } else {
        return 0;
    }
}

void AVLTree::updateHeight(AVLNode* node) {// обновляет высоту дерева на основе дочерних узлов
    if (node) {
        node->height = max(height(node->left), height(node->right)) + 1; // максимальное значение + 1 для текущего узла
    }
}

// Когда у баланс больше 1, а х больше 0
AVLNode* AVLTree::rotateRight(AVLNode* y) {// правый поворот для балансировки дерева
    AVLNode* x = y->left; // x - левый ребенок y
    AVLNode* T2 = x->right; // T2 - правый ребенок x
    x->right = y; // x становится новым корнем, y - правым ребенком x
    y->left = T2; // T2 теперь - левым ребенком y
    updateHeight(y); // обновляем высоту y
    updateHeight(x); // обновляем высоту x
    return x; // возвращаем новый корень
}

// используется, когда х меньше -1, у имеет баланс <0
AVLNode* AVLTree::rotateLeft(AVLNode* x) {// левый поворот для балансировки дерева
    AVLNode* y = x->right; // y - правый ребенок x
    AVLNode* T2 = y->left; // T2 - левый ребенок y
    y->left = x; // y становится новым корнем, x - левым ребенком y
    x->right = T2; // T2 теперь - правым ребенком x
    updateHeight(x); // обновляем высоту x
    updateHeight(y);// обновляем высоту y
    return y; // возвращаем новый корень
}

AVLNode* AVLTree::balance(AVLNode* node) {// проверяет баланс и выполняет повороты, если нужно
    updateHeight(node);
    int balance = balanceFactor(node);
    if (balance > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (balance < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

AVLNode* AVLTree::insert(AVLNode* node, std::string key) {// вставляем узел в дерево и балансируем
    if (!node) { // если узел пустой, то создаем новый
        return new AVLNode(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key); // вставлем в левое поддерево, если новое значение меньше текущего
    } else if (key > node->key) {
        node->right = insert(node->right, key); // вставляем в правое поддерево
    } else {
        return node; // дубликаты не допускаются
    }
    //return node;
    return balance(node);
}

void AVLTree::insert(const std::string& key) {
    root = insert(root, key); // Обновляем корень после вставки
    saveToFile("AVLtree.data"); // Сохраняем состояние дерева
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {// находим самый левый узел (минимальное значение)
    AVLNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

AVLNode* AVLTree::remove(AVLNode* node, std::string key) {// удаляем узел и балансируем
    if (!node) {
        return node; // если узел пустой, то ничего не делаем
    }
    if (key < node->key) {
        node->left = remove(node->left, key); //рекурсивно удаляем из левого поддерева
    } else if (key > node->key) {
        node->right = remove(node->right, key); // рекурсивно удаляем из правого поддерева
    } else {
        // узел найден
        if (!node->left) {
            AVLNode* temp = node->right; // если нет левого дочернего узла
            delete node; //удаляем текущий узел
            return temp; // возвращаем правое поддерево
        } else if (!node->right) {
            AVLNode* temp = node->left; // если нет правого дочернего узла
            delete node; // удаляем текущий узел
            return temp; // возвращаем левое поддерево
        }
        // узел с двумя дочерними узлами
        AVLNode* temp = minValueNode(node->right); //находим минимальный узел в правом поддереве
        node->key = temp->key; // копируем в текущий узел
        node->right = remove(node->right, temp->key); // удаляем минимальный узел в правом поддереве
    }
    //return node;
    return balance(node);
}

void AVLTree::remove(const std::string& key) {
    root = remove(root, key); // Обновляем корень после удаления
    saveToFile("AVLtree.data"); // Сохраняем состояние дерева
}

bool AVLTree::search(AVLNode* node, std::string key) {// проверяем есть ли узел в дереве с нужным значением
    if (!node){
        return false;
    } 
    if (key == node->key) {
        return true;
    }
    if (key < node->key) {
        return search(node->left, key); // Если ключ меньше, ищем в левом поддереве
    } else {
        return search(node->right, key); // В противном случае, ищем в правом поддереве
    }
}

void AVLTree::inOrder(AVLNode* node) { // симметричный обход для рекурсивного вывода
    if (node) {
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
    }
}

void AVLTree::inOrder() { // симметричный обход без параметров
    if (root) {
        inOrder(root); // вызываем обход, начиная с корня
    } else {
        std::cout << "AVL tree is empty" << std::endl;
    }
}

void AVLTree::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }

    saveNode(root, file); // начинаем с корня дерева
    file.close();
}

void AVLTree::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }

    clear(); // очищаем текущее дерево перед загрузкой

    std::string key;
    while (std::getline(file, key)) {
        root = insert(root, key); // обновляем корень
    }

    file.close();
}