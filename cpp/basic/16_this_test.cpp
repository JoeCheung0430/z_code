#include <iostream>
using namespace std;

class person
{
public:
    person(int age)
    {
        m_age = age;
    }

    person &person_age_add(person p)
    {
        this->m_age += p.m_age;
        return *this;
    }

    int m_age;
};

void test01()
{
    person p1(10);
    person p2(10);
    cout << "p1 age:" << p1.m_age << endl;
    cout << "p2 age:" << p2.m_age << endl;
    p2.person_age_add(p1).person_age_add(p1).person_age_add(p1);
    cout << "p2 age:" << p2.m_age << endl;
}

int main()
{
    test01();
    return 0;
}