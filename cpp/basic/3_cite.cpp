#include <iostream>
using namespace std;

void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int &text01()
{
    //int c = 10;
    static int c = 10;
    return c;
}

int main()
{
    int a = 10, b = 20;
    swap(a, b);
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    int &c = text01();
    cout << "c=" << c << endl;
    c = 1000;
    cout << "c=" << c << endl;
    system("pause");
    return 0;
}