#include <iostream>
#include <thread>
#include <chrono>

void client(int& counter)
{
    while (counter < 10)
    {
        std::cout << "Счетчик клиента: " << counter << std::endl;
        counter++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

void operationist(int& counter)
{
    while (counter > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        counter--;
        std::cout << "Взял в работу клиента. Очередь: " << counter << std:: endl;
    }
}

int main()
{
    int counter{};
    std::thread t1{client, std::ref(counter)};
    std::thread t2{operationist, std::ref(counter)};
    t1.join();
    t2.join();
    return 0;
}