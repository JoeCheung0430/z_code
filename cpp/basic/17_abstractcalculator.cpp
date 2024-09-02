#include<iostream>
using namespace std;

class AbstractCalculator{
public:
    virtual int getresult()
    {
        return 0;
    }
    int m_num1;
    int m_num2;

    virtual ~AbstractCalculator()
    {}
};

class AddCalculator :public AbstractCalculator{
public:
    int getresult()
    {
        return m_num1 + m_num2;
    }
};

class SubCalculator :public AbstractCalculator{
public:
    int getresult()
    {
        return m_num1 - m_num2;
    }
};

class MulCalculator :public AbstractCalculator{
public:
    MulCalculator(int m1,int m2)
    {
        m_num1 = m1;
        m_num2 = m2;
    }
    int getresult()
    {
        return m_num1 * m_num2;
    }
};


void test()
{
    AbstractCalculator *ptr = new AddCalculator;
    ptr->m_num1 = 30;
    ptr->m_num2 = 20;
    cout << ptr->m_num1 << " + " << ptr->m_num2 << " = " << ptr->getresult() << endl;
    delete ptr;
    ptr = new SubCalculator;
    ptr->m_num1 = 30;
    ptr->m_num2 = 20;
    cout << ptr->m_num1 << " - " << ptr->m_num2 << " = " << ptr->getresult() << endl;
    delete ptr;
    cout << MulCalculator(10, 10).getresult() << endl;
}

int main()
{
    test();
    return 0;
}