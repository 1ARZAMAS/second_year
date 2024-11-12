#include "header.h"

int main(int argc, char* argv[]) {
    std::string filename;
    // Интерактивный ввод команд
    std::string query;
    cout << "Enter the command (ot 'exit' to exit):" << endl;
    while (true) {
        cout << "> ";
        getline(cin, query);
        if (query == "exit") {
            break; // Выход из цикла
        }
        processQuery(query);
    }
    return 0;
}
