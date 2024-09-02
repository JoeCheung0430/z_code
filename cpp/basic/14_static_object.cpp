#include <iostream>
using namespace std;

class person{
public:
    static int m_a;

    static void func()
    {
        cout << "static" << endl;
    }
};

int person::m_a = 10;

void test01()
{
    person p;
    cout << p.m_a << endl;
    person::func();
}

int main()
{
    test01();
    return 0;
}