#include <iostream>
#include <thread>
#include <mutex>

int apple = 0;
std::timed_mutex mtx;

void myprint(int n)
{
    for (int i = 0; i < 2;i++)
    {
        std::cout << n << " thread in" << std::endl;
        std::unique_lock<std::timed_mutex> unq(mtx, std::defer_lock);
        if(unq.try_lock_for(std::chrono::seconds(2)))
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            apple++;
            std::cout << n << " thread using mutex" << std::endl;
        }
    }
}


int main()
{
    std::thread t1(myprint, 1);
    std::thread t2(myprint, 2);
    t1.join();
    t2.join();
    std::cout << apple << std::endl;
    return 0;
}