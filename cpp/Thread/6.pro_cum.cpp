#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> q1;
std::mutex mtx;
std::condition_variable cv;

void Producer()
{
    for (int i = 0; i < 10; i++)
    {
    {
        std::unique_lock<std::mutex> lock(mtx);
        q1.push(i);
        cv.notify_one();
        std::cout << "Producer push" << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

bool isempty()
{
    bool isem = q1.empty();
    return !isem;
}

void Comsumer()
{
    while(1) 
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock,isempty);
        int value = q1.front();
        q1.pop();
        std::cout << "Comsumer pop" << value << std::endl;
    }
}
   

void thread_task()
{
    std::thread t1(Producer);
    std::thread t2(Comsumer);
    t1.join();
    t2.join();
}

int main()
{
    thread_task();
    system("pause");
    return 0;
}