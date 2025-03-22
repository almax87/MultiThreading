#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

std::mutex cout_mutex;

void calculate (long int count_length, int thread_num, std::atomic<bool>& done_flag)
{
    auto start_time = std::chrono::steady_clock::now();
    long double j{};
    std::thread::id thread_id = std::this_thread::get_id();
    for (int i = 1; i <= count_length; i++)
    {
        cout_mutex.lock();
        std::cout << "\033[" << thread_num << ";1H"; 
        std::cout << "\rThread_id: " << thread_id << "[";
        j = sqrt(i);
        int progress = static_cast<double>(i)/static_cast<double>(count_length)*10;
        for (int z = 0; z < 10; z++)
        {
            if (z < progress)
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << "] " << progress*10 << "%";
        cout_mutex.unlock();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end_time = std::chrono::steady_clock::now();
    done_flag = true;
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    {
        std::lock_guard<std::mutex> lk(cout_mutex);
        std::cout << "\033[" << thread_num << ";1H"; 
        std::cout << "\rThread_id: " << thread_id << "[";
        for (int z = 0; z < 10; z++)
        {
            std::cout << "=";
        }
        std::cout << "] 100%. Elapsed time: " << elapsed_time.count() << "ms.";
    }
}

int main()
{
    int count_threads{10};
    auto count_length{10000};
    std::thread::id thread_id{};
    std::vector <std::atomic<bool>> done_flags(count_threads);
    std::vector<std::thread> thread_list{};
    for (auto i = 0; i < count_threads; i++)
    {
        done_flags[i] = false;
        thread_list.emplace_back(calculate, count_length, i+1, std::ref(done_flags[i]));
    }

    for (auto& i : thread_list)
    {
        i.join();
        {
            std::lock_guard<std::mutex>lk(cout_mutex);
            std::cout << std::endl;
        }
    }
    std::cout << "All threads have finished calculations." << std::endl;
    return 0;
}