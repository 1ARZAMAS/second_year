/*
Спинлок - низкоуровневый примитив синхронизации, применяемый для
реализации взаимного исключения исполнения критических участков кода
с использованием цикла активного ожидания. Применяется в случаях, когда
ожидание захвата блокировки предполагается недолим.
Спинлоки не задействуют планировщик, что позволяет не тратить время
на блокировку/разблокировку состояния потока. С другой стороны нагружает
процессор во время активного ожидания
*/

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

using namespace std;

class SpinLock{
public:
    SpinLock() : flag(ATOMIC_FLAG_INIT) {}

    void lock(){
        while (flag.test_and_set(memory_order_acquire)) {}
    }
    void unlock(){
        flag.clear(memory_order_release);
    }
private:
    atomic_flag flag;
};

SpinLock spinlock;

void randomChars(int thread_id, int letter_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(32, 126);  // ASCII диапазон видимых символов
    string chars;
    spinlock.lock();
    for (int i = 0; i < letter_count; ++i){
        char letter = static_cast<char>(dis(gen));
        chars += letter;
    }
    cout << "Thread " << thread_id << ": " << chars << endl;  
    spinlock.unlock();
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