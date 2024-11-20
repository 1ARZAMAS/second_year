/*
semaphore — это стандартный примитив синхронизации, который 
позволяет ограничить количество потоков, которые могут одновременно 
захватывать ресурсы.
*/

#include <iostream>
#include <random>
#include <string>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std;

counting_semaphore<1> sem(1);
// первая 1 - количество разрешений, который семафор может максимум выделить
// вторая 1 - количество доступных разрешений, те
// один поток сразу же получит разрешение

void randomChars(int thread_id, int letter_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(32, 126);  // ASCII диапазон видимых символов
    string chars;
    sem.acquire();
    for (int i = 0; i < letter_count; ++i){
        char letter = static_cast<char>(dis(gen));
        chars += letter;
    }
    cout << "Thread " << thread_id << ": " << chars << endl;  
    sem.release();
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