#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

class Philosopher {
public:
    Philosopher(int id, int left_fork_id, int right_fork_id, mutex& _first_fork, mutex& _second_fork)
        : id(id), left_fork_id(left_fork_id), right_fork_id(right_fork_id), left_fork(_first_fork), right_fork(_second_fork) {}

    void action() {
        while (true) {
            // Думаем
            {
                lock_guard<mutex> lock(output_mutex);
                cout << "Philosopher " << id << " is thinking..." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1000)); // думаем 1 секунду

            // Захват вилок
            lock(left_fork, right_fork); // фиксируем обе вилки
            lock_guard<mutex> lg1(left_fork, adopt_lock); // левая вилка
            lock_guard<mutex> lg2(right_fork, adopt_lock); // правая вилка

            // Едим
            {
                lock_guard<mutex> lock(output_mutex);
                cout << "Philosopher " << id << " is eating..." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(2000)); // кушаем 2 секунды

            // Освобождаем вилки
            {
                lock_guard<mutex> lock(output_mutex);
                cout << "Philosopher " << id << " released forks " << left_fork_id << " and " << right_fork_id << endl; // выводим индексы вилок
            }
        }
    }

private:
    int id;
    int left_fork_id;
    int right_fork_id;
    mutex& left_fork;
    mutex& right_fork;
    static mutex output_mutex;
};

mutex Philosopher::output_mutex; // мьютекс для вывода

int main() {
    const int num_threads = 5;
    vector<thread> philosophers_threads; // вектор для потоков
    vector<mutex> forks(num_threads); // мьютексы для вилок

    // Создаем философов
    for (int i = 0; i < num_threads; ++i) {
        mutex& left_fork = forks[(i + 4) % num_threads];
        mutex& right_fork = forks[i];
        philosophers_threads.emplace_back(&Philosopher::action, Philosopher(i, (i + 4) % num_threads, i, left_fork, right_fork));
    }

    for (auto& thread : philosophers_threads) {
        thread.join();
    }

    return 0;
}
