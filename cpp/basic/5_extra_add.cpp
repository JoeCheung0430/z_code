#include <iostream>
using namespace std;

class Person
{
public:
    Person operator+(Person &p)
    {
        Person temple;
        temple.m_age = this->m_age + p.m_age;
        return temple;
    }
    int m_age;
};

void test()
{
    Person p1;
    p1.m_age = 10;
    Person p2;
    p2.m_age = 10;
    Person p3;
    p3 = p1 + p2;
    cout << "p3 age:" << p3.m_age << endl;
}

int main()
{
    test();
    return 0;
}