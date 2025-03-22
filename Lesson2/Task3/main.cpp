#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    int value;
    std::mutex mtx;

    Data(int val) : value(val) {}

    void print() const {
        std::cout << "Data: " << value << std::endl;
    }
};

// Вариант 1: Использование std::lock и std::lock_guard
void swap_with_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx); // Захватываем оба мьютекса
    std::lock_guard<std::mutex> lock_a(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(b.mtx, std::adopt_lock);

    std::swap(a.value, b.value);
}

// Вариант 2: Использование std::scoped_lock
void swap_with_scoped_lock(Data& a, Data& b) {
    std::scoped_lock lock(a.mtx, b.mtx); // Захватываем оба мьютекса автоматически

    std::swap(a.value, b.value);
}

// Вариант 3: Использование std::unique_lock
void swap_with_unique_lock(Data& a, Data& b) {
    std::unique_lock<std::mutex> lock_a(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(b.mtx, std::defer_lock);
    std::lock(lock_a, lock_b); // Захватываем оба мьютекса

    std::swap(a.value, b.value);
}

int main() {
    Data data1(10);
    Data data2(20);

    std::cout << "Before swap:" << std::endl;
    data1.print();
    data2.print();

    // Используем разные варианты swap
    swap_with_lock(data1, data2);
    std::cout << "After swap_with_lock:" << std::endl;
    data1.print();
    data2.print();

    swap_with_scoped_lock(data1, data2);
    std::cout << "After swap_with_scoped_lock:" << std::endl;
    data1.print();
    data2.print();

    swap_with_unique_lock(data1, data2);
    std::cout << "After swap_with_unique_lock:" << std::endl;
    data1.print();
    data2.print();

    return 0;
}
