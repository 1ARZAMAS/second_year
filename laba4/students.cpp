#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

struct Student {
    string name;
    int course;
    int debt;
};

// Глобальная очередь индексов студентов и необходимые примитивы синхронизации
queue<int> student_indices; // Очередь индексов студентов
mutex mtx; // Мьютекс для доступа к очереди
condition_variable cv; // Условная переменная для ожидания наличия задач

string nameGenerator(){
    vector<string> surnames = {"Иванов", "Смирнов", "Кузнецов", "Попов", "Васильев", "Петров", "Соколов", "Михайлов", "Новиков",
    "Фёдоров", "Морозов", "Волков", "Алексеев", "Лебедев", "Семёнов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев",
    "Орлов", "Андреев", "Макаров", "Никитин", "Захаров"};
    vector<string> names = {"Александр", "Данила", "Алексей", "Кирилл", "Сергей", "Никита", "Андрей", "Артём", "Дмитрий",
    "Иван", "Михаил", "Пётр", "Павел", "Егор", "Илья", "Матвей", "Константин", "Максим", "Виктор", "Григорий"};
    string result = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()];
    return result;
}

void process_student(const vector<Student>& students, vector<string>& to_expel, int course, int debtsAmount) {
    while (true) {
        int idx = -1;
        unique_lock<mutex> lock(mtx); // мьютекс для защиты доступа

        if (student_indices.empty()) { // если очередь пуста, то выходим из цикла
            break;
        }
        
        idx = student_indices.front(); // в противном случае берем индекс студента из очереди
        student_indices.pop();
        if (students[idx].debt > debtsAmount && students[idx].course > course) { // и обрабатываем условия для отчисления
            to_expel.push_back(students[idx].name);
        }
    }
}

int main(){
    int studentsAmount;
    int threadsAmount;
    int course;
    int debtsAmount;
    cout << "Enter amount of students: ";
    cin >> studentsAmount;
    cout << "Enter amount of threads: ";
    cin >> threadsAmount;
    cout << "Enter course: ";
    cin >> course;
    cout << "Enter amount of debts: ";
    cin >> debtsAmount;
    vector<Student> students;
    for (int i = 0; i < studentsAmount; i++){ // пройдемся по всему вектору и заполним его случайными данными
        students.push_back({nameGenerator(), rand() % 5 + 1, rand() % 11});
    }

    vector<string> to_expel;  // вектор студентов на отчисление

    // заполняем очередь индексами студентов
    for (int i = 0; i < students.size(); ++i) {
        student_indices.push(i);
    }

    // запуск с многозадачностью
    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < threadsAmount; ++i) {
        threads.push_back(thread(process_student, cref(students), ref(to_expel), course, debtsAmount));
    }

    for (auto& t : threads) { // ждем завершения всех потоков
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "With multithreads, time taken: " << duration.count() << " ms" << endl;

    threads.clear();

    cout << "Students to expel:" << endl;
    for (const auto& name : to_expel) {
        cout << name << endl;
    }

    // запуск без многозадачности
    auto startAgain = chrono::high_resolution_clock::now();
    
    // запускаем один поток для выполнения задачи
    thread single_thread(process_student, cref(students), ref(to_expel), course, debtsAmount);
    single_thread.join(); // ждем завершения потока

    auto endAgain = chrono::high_resolution_clock::now();
    auto durationAgain = chrono::duration_cast<chrono::microseconds>(endAgain - startAgain);
    cout << "Without multithreads, time taken: " << durationAgain.count() << " ms" << endl;

    cout << "Students to expel:" << endl;
    for (const auto& name : to_expel) {
        cout << name << endl;
    }

    return 0;
}