#include <iostream>
using namespace std;

int *func()
{
    int *p = new int(10);
    return p;
}

void test01()
{
    int *p = func();
    cout << "test01:" << *p << endl;
    delete p;
}

void test02()
{
    int *arr = new int[10];
    for (int i = 0; i < 10;i++)
    {
        arr[i] = i;
    }
    cout << "test02:" << endl;
    for (int j = 0; j < 10;j++)
    {
        cout << arr[j] << "  ";
    }
    cout << endl;
}

int main()
{
    test01();
    test02();
    return 0;
}