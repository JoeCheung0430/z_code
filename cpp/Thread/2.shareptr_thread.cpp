#include <iostream>
using namespace std;
#include <thread>
#include <memory>

class A
{
private:
    friend void thread_task();
    void my_print()
    {
        cout << "hello world" << endl;
    }
};

void thread_task()
{
    shared_ptr<A> a = make_shared<A>();
    //运行时用下面的运行，因为mac的clang不支持c++11，会红，我强迫症看不得，但代码没问题
    //thread t(&A::my_print, a);
    thread t;
    t.join();
}

int main()
{
    thread_task();
    return 0;
}