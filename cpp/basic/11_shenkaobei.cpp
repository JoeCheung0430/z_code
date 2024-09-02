#include <iostream>
using namespace std;

class person
{
public:
    person()
    {
        cout << "1" << endl;
    }
    person(int age,int height)
    {
        m_age = age;
        m_height = new int(height);
        cout << "2" << endl;
    }
    person(const person &p)
    {
        m_age = p.m_age;
        m_height = new int(*p.m_height);
        cout << "3" << endl;
    }
    ~person()
    {
        if(m_height!=NULL)
        {
            delete m_height;
            m_height = NULL;
        }
        cout << "4" << endl;
    }
    
    int m_age;
    int *m_height;
};

void test01()
{
    person p1(20,170);
    person p2(p1);
    cout << "p1 age:" << p1.m_age << endl;
    cout << "p1 height:" << *p1.m_height << endl;
    cout << "p2 age:" << p2.m_age << endl;
    cout << "p2 height:" << *p2.m_height << endl;
}

int main()
{
    test01();
    return 0;
}