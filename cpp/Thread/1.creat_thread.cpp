#include <iostream>
using namespace std;
#include <thread>
#include <string>


void my_print()
{
    cout << "hello world" << endl;
}

void thread_task()
{
    thread thread1(my_print);
    bool isable= thread1.joinable();
    if(isable)
    {
        thread1.join();
    }
}

int main()
{
    thread_task();
    return 0;
}