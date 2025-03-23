#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <thread>

// Функция для параллельного выполнения for_each
template<typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func&& func, size_t block_size) {
    // Вычисляем длину контейнера
    size_t length = std::distance(begin, end);

    // Если длина меньше или равна размеру блока, выполняем обработку последовательно
    if (length <= block_size) {
        std::for_each(begin, end, func);
    } else {
        // Находим середину контейнера
        Iterator mid = begin;
        std::advance(mid, length / 2);

        // Рекурсивно запускаем параллельную обработку для каждой половины
        auto future = std::async(std::launch::async, [=, &func]() {
            parallel_for_each(begin, mid, func, block_size);
        });

        // Обрабатываем вторую половину в текущем потоке
        parallel_for_each(mid, end, func, block_size);

        // Дожидаемся завершения асинхронной задачи
        future.get();
    }
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Функция для обработки элементов (например, умножение на 2)
    auto process_func = [](int& value) {
        value *= 2;
    };

    // Размер блока для разделения контейнера
    size_t block_size = 3;

    // Выполняем параллельный for_each
    parallel_for_each(data.begin(), data.end(), process_func, block_size);

    // Выводим результат
    std::cout << "Processed data: ";
    for (const auto& value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}