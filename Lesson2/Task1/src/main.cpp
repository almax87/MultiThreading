#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void client(std::atomic<int>& counter, std::memory_order order)
{
    while (counter < 10)
    {
        counter.fetch_add(1);
        std::cout << "Счетчик клиента: " << counter.load() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}

void operationist(std::atomic<int>& counter, std::memory_order order)
{
    while (counter > 0)
    {
        counter.fetch_sub(1);
        std::cout << "Взял в работу клиента. Очередь: " << counter.load() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    std::memory_order order = std::memory_order_seq_cst;
    std::atomic<int> counter{};
    std::thread t1{client, std::ref(counter), order};
    std::thread t2{operationist, std::ref(counter), order};
    t1.join();
    t2.join();
    return 0;
}