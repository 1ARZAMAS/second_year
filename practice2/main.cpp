#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h> // функции для работы с сокетами
#include <netinet/in.h> // структуры данных для портов
#include <unistd.h> // функции для работы с системными вызовами

#include <thread>
#include <sstream>
#include <mutex>

#include "header.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

int main() {
    mutex mtx;
    DatabaseManager dbManager;
    DBtable dbTableManager;
    DBtable table;
    loadSchema(dbManager, "schema.json");
    createDirectoriesAndFiles(dbManager);

    cout << "Starting server..." << endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // создание сокета для сервера: AF_INET для IPv4, сок для работы с ТСР, 0 по дефолту
    if (serverSocket == -1) {
        cerr << "Error wile making socket" << endl;
        return 1;
    }

    sockaddr_in serverAddress; // храним адрес сокета
    serverAddress.sin_family = AF_INET; // указываем на семейство адресов
    serverAddress.sin_addr.s_addr = INADDR_ANY; // принимаем соединения с любого айпишника
    serverAddress.sin_port = htons(7432); // порт указываем 7432 по тз

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) { // если произошла какая-то ошибка во время привязки
        cerr << "Connection is not successeed" << endl; // сокета к серверу то вернем ошибку
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 4) < 0) { // будем ожидать только 4 подключения, в очереди на подключение может быть только четыре клиента
        cerr << "Error while listening" << endl;
        close(serverSocket);
        return 1;
    }
    cout << "Waiting for the connection..." << endl;

    while (true) { 
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int newSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength); // ожидаем подключение клиента и создаем для него новый сокет
        if (newSocket < 0) {
            cerr << "Connection is not established" << endl;
            break;
        }
        cout << "Connection established" << endl;

        thread([newSocket, &dbManager, &mtx, &table] () { // создаем поток для каждого клиента
            char buffer[1024] = {0}; 
            while (true) {
                int valread = read(newSocket, buffer, 1024); // считываем данные в буфер, если клиент отсоединился, то вернем 0 или отриц значение
                if (valread <= 0) {
                    cerr << "Client disconnected" << endl;
                    close(newSocket);
                    break;
                }
                string command(buffer, valread);
                {
                    lock_guard<mutex> lock(mtx);
                    cout << "Command received: " << command;
                    if (command.find("exit") != string::npos) {
                        close(newSocket);
                        break;
                    } else if (command.find("INSERT") != string::npos) {
                        insert(command, dbManager, table);
                    } else if (command.find("SELECT") != string::npos) {
                        select(command, dbManager, table);
                    } else if (command.find("DELETE") != string::npos) {
                        delete1(command, dbManager, table);
                    } else {
                        cerr << "Unknown command" << endl;
                    }    
                }
                send(newSocket, buffer, valread, 0); // отправляем данные обратно клиенту
                memset(buffer, 0, sizeof(buffer)); // чистим за собой буфер
            }
        }).detach(); // отсоединяем поток чтобы он сам работал
    }

    close(serverSocket); // завершаем работу сервера
    return 0;
}
