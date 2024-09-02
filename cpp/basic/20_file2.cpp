#include <iostream>
using namespace std;
#include <fstream>

class person{
public:
    char m_name[40];
    int m_age;
};

void test()
{
    #if 0
    fstream fd1;
    fd1.open("/Users/cheungcoekbun/Desktop/test.txt", ios::out | ios::binary);
    person p={"张三",18};
    fd1.write((const char *)&p, sizeof(p));
    fd1.close();
    #endif
    
    #if 1
    fstream fd2;
    fd2.open("/Users/cheungcoekbun/Desktop/test.txt", ios::in | ios::binary);
    if(!fd2.is_open())
    {
        cout << "error" << endl;
        return;
    }
    person p2;
    fd2.read((char *)&p2, sizeof(p2));
    cout << p2.m_name << " " << p2.m_age << endl;
    fd2.close();
    #endif
}

int main()
{
    test();
    return 0;
}