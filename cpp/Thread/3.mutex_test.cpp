#include <iostream>
using namespace std;
#include <thread>
#include <mutex>

int a = 0;
mutex mtx;

void my_print()
{

    for (int i = 0; i < 10000; i++)
    {
        mtx.lock();
        a += 1;
        mtx.unlock();
    }
}

void thread_test()
{
    thread t1(my_print);
    thread t2(my_print);

    t1.join();
    t2.join();

    cout << a << endl;
}

int main()
{
    thread_test();
    return 0;
}
