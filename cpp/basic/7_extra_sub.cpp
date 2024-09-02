#include <iostream>
using namespace std;

class myInteget{
    friend ostream &operator<<(ostream &cout, myInteget myint);

public:
    myInteget()
    {

    }
    myInteget(int num)
    {
        m_int = num;
    }

    //before
    myInteget& operator--()
    {
        m_int--;
        return *this;
    }
    //after
    myInteget operator--(int)
    {
        myInteget temp = *this;
        m_int--;
        return temp;
    }

private:
    int m_int;
};

ostream& operator<<(ostream &cout,myInteget myint)
{
    cout << myint.m_int << endl;
    return cout;
}

void test()
{
    myInteget myint(10);
    cout << --myint << endl;
    cout << myint << endl;

    cout << myint-- << endl;
    cout << myint << endl;
}

int main()
{
    test();
    return 0;
}