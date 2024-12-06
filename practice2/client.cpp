#include <iostream>
#include <sys/socket.h> // функции для работы с сокетами
#include <netinet/in.h> // структуры данных для портов
#include <arpa/inet.h> // функции для работы с сетевыми адресами
#include <unistd.h> // функции для работы с системными вызовами
#include <string.h>

using namespace std;

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет
    if (clientSocket == -1) {
        cerr << "Unable to create socket" << endl;
        return 1;
    }
    sockaddr_in serverAddress; // храним инфу о сетевом адресе
    serverAddress.sin_family = AF_INET; // семейство протоколов IPv4
    serverAddress.sin_port = htons(7432); // порт 7432

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) { // преобразует текстовое представление IP-адреса в двоичную форму
        cerr << "Incorrect adress" << endl;
        close(clientSocket);
        return 1;
    }
    // соединение с сервером
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) { // пытаемся подключиться к серверу
        cerr << "Connection failed" << endl;
        close(clientSocket);
        return 1;
    }

    char buffer[1024] = {0}; // создаем буфер в котором будут храниться данные, полученные от сервера
    while (true) {
        cout << "Enter command: ";
        string text;
        getline(cin, text);
        text += "\n"; // добавляем в конце /n так как это стандарт для протокола, сообщает о конце команды
        send(clientSocket, text.c_str(), text.length(), 0); // отправляет сообщение на сервер, c_str - строка, преобразованная в массив символов, 0 - обычные параметры
        int valread = read(clientSocket, buffer, 1024); // чтение данных в буфер, valread - количество байт
        if (valread <= 0) {
            cerr << "Server disconnected" << endl;
            break;
        }

        cout << "Message from the server: " << buffer;
        memset(buffer, 0, sizeof(buffer)); // очищаем и заполняем буфер нулями
    }
    close(clientSocket);
    return 0;
}