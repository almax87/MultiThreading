#include <iostream>
#include <vector>
#include <future>
#include <algorithm>

// Функция для поиска минимального элемента в подмассиве
int findMinIndex(const std::vector<int>& arr, int start) {
    int minIndex = start;
    for (int i = start + 1; i < arr.size(); ++i) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Асинхронная задача для поиска минимального элемента
std::future<int> asyncFindMinIndex(const std::vector<int>& arr, int start) {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    // Запускаем асинхронную задачу
    std::thread([&arr, start, promise = std::move(promise)]() mutable {
        int minIndex = findMinIndex(arr, start);
        promise.set_value(minIndex);
    }).detach();

    return future;
}

// Функция сортировки выбором
void selectionSort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        // Запускаем асинхронную задачу для поиска минимального элемента
        std::future<int> future = asyncFindMinIndex(arr, i);

        // Получаем индекс минимального элемента
        int minIndex = future.get();

        // Меняем местами текущий элемент с минимальным
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
    std::vector<int> arr = {64, 25, 12, 22, 11};

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    selectionSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}