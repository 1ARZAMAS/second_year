/*
Легковесная версия семафора, для использования в многопоточных 
приложениях, где требуется синхронизация потоков, более 
эффективен по сравнению с обычным, использует меньше ресурсов
*/

#include <iostream>
#include <random>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

using namespace std;

class SemaphoreSlim {
public:
    explicit SemaphoreSlim(int initial_count) : count(initial_count) {}

    void Acquire(){
        unique_lock<std::mutex> lock(Mutex);
        cv.wait(lock, [this]() {return count > 0; }); // ждем освобождения ресурса
        --count; // забираем ресурс
    }

    void Release(){
        lock_guard<std::mutex> lock(Mutex);
        ++count; // освобождаем ресурс
        cv.notify_one(); // оповещаем один поток о свободном ресурсе
    }
private:
    mutex Mutex; // мьютекс для синхронизации
    condition_variable cv; // условная переменная для ожидания
    int count; //количество доступных ресурсов
};

SemaphoreSlim semaphoreslim(1); // только 1 поток может работать одновременно

void randomChars(int thread_id, int letter_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(32, 126);  // ASCII диапазон видимых символов
    string chars;
    semaphoreslim.Acquire();
    for (int i = 0; i < letter_count; ++i){
        char letter = static_cast<char>(dis(gen));
        chars += letter;
    }
    cout << "Thread " << thread_id << ": " << chars << endl;  
    semaphoreslim.Release();
}

int main(){
    using namespace std::chrono;

    vector<thread> threads;
    auto start = high_resolution_clock::now(); // начало таймера
    
    for (int i = 0; i < 4; ++i) { // Запуск потоков
        threads.push_back(thread(randomChars, i, 10));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now(); // конец таймера
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    return 0;
}