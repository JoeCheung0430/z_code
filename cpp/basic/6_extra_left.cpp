#include <iostream>
using namespace std;

class person{

    friend ostream& operator<<(ostream &cout, person &p);

public:
    person(int age1,int age2)
    {
        m_age1 = age1;
        m_age2 = age2;
    }

private:
    int m_age1;
    int m_age2;
};

ostream& operator<<(ostream &cout,person &p)
{
    cout << "m_age1:" << p.m_age1 << endl;
    cout << "m_age1:" << p.m_age1 << endl;
    return cout;
}

void test()
{
    person p(10, 10);
    cout << p << endl;
}

int main()
{
    test();
    return 0;
}