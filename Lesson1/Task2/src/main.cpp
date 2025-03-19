#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Функция для вычисления суммы двух векторов в заданном диапазоне
void vectorSum(const std::vector<int>& vec1, const std::vector<int>& vec2, std::vector<int>& result, int start, int end) {
    for (int i = start; i < end; ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

// Функция для запуска вычислений в нескольких потоках
void parallelVectorSum(const std::vector<int>& vec1, const std::vector<int>& vec2, std::vector<int>& result, int numThreads) {
    std::vector<std::thread> threads;
    int chunkSize = vec1.size() / numThreads;
    int start = 0;
    int end = chunkSize;

    for (int i = 0; i < numThreads; ++i) {
        if (i == numThreads - 1) {
            end = vec1.size(); // Последний поток обрабатывает оставшиеся элементы
        }
        threads.emplace_back(vectorSum, std::ref(vec1), std::ref(vec2), std::ref(result), start, end);
        start = end;
        end += chunkSize;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    // Определяем доступное количество аппаратных ядер
    unsigned int numCores = std::thread::hardware_concurrency();
    std::cout << "Доступное количество аппаратных ядер: " << numCores << std::endl;

    // Размеры массивов для тестирования
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};
    std::vector<int> numThreads = {2, 4, 8, 16};

    // Таблица для хранения результатов
    std::vector<std::vector<double>> results(sizes.size(), std::vector<double>(numThreads.size(), 0.0));

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        std::vector<int> vec1(size, 1); // Заполняем векторы единицами
        std::vector<int> vec2(size, 2);
        std::vector<int> result(size);

        for (size_t j = 0; j < numThreads.size(); ++j) {
            int threads = numThreads[j];

            auto start = std::chrono::high_resolution_clock::now();
            parallelVectorSum(vec1, vec2, result, threads);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            results[i][j] = duration.count();
        }
    }

    // Вывод таблицы результатов
    std::cout << "\nТаблица результатов:\n";
    std::cout << "Размер массива\\Потоков\t";
    for (int threads : numThreads) {
        std::cout << threads << "\t\t";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << sizes[i] << "\t\t\t";
        for (size_t j = 0; j < numThreads.size(); ++j) {
            std::cout << results[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}