/*
Барьерная синхронизация - метод синхронизации в распределенных
вычислениях (Распределённые вычисления — способ решения трудоёмких 
вычислительных задач с использованием нескольких компьютеров, 
чаще всего объединённых в параллельную вычислительную систему),
при котором выполнение параллельного алгоритма или его части 
можно разделить на несколько этапов, разделённых барьерами
Барьер для группы потоков (или процессов) в исходном коде означает, 
что каждый поток (процесс) должен остановиться в этой точке и 
подождать достижения барьера всеми потоками (процессами) группы. 
Когда все потоки (процессы) достигли барьера, их выполнение продолжается
*/

#include <iostream>
#include <random>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <barrier>

using namespace std;
using namespace std::chrono;

mutex Mutex;

void randomChars(int thread_id, int letter_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(32, 126);  // ASCII диапазон видимых символов
    string chars;
    for (int i = 0; i < letter_count; ++i){
        char letter = static_cast<char>(dis(gen));
        chars += letter;
    }
    cout << "Thread " << thread_id << ": " << chars << endl; 
}

void worker(int id, barrier<>& barrier, int letter_count){
    barrier.arrive_and_wait();
    lock_guard<std::mutex> lock(Mutex);
    randomChars(id, letter_count);// Генерация случайных символов
}

int main(){
    vector<thread> threads;
    barrier<> barrier(4);
    auto start = high_resolution_clock::now(); // начало таймера
    for (int i = 0; i < 4; ++i) { // Запуск потоков
        threads.push_back(thread(worker, i, ref(barrier), 10));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now(); // конец таймера
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds\n";
}