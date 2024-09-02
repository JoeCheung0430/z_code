#include <iostream>
using namespace std;

template <typename T>
void myswap(T &a,T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 10;
    int b = 20;
    myswap(a, b);
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    float c = 10.1;
    float d = 20.1;
    myswap(c, d);
    cout << "c:" << c << endl;
    cout << "d:" << d << endl;
    return 0;
}