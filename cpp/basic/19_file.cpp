#include <iostream>
using namespace std;
#include <fstream>
#include <string>

void test01()
{
    ofstream fd1;
    fd1.open("/Users/cheungcoekbun/Desktop/test.txt", ios::out);
    fd1 << "hello world!" << endl;
    fd1 << "hello world!" << endl;
    fd1.close();

    ifstream fd2;
    fd2.open("/Users/cheungcoekbun/Desktop/test.txt", ios::in);
    if(!fd2.is_open())
    {
        cout << "error" << endl;
    }
    /*
        char buf[1024] = {0};
        while(fd2.getline(buf,sizeof(buf)))
        {
            cout << buf << endl;
        }
    */
    string buf;
    while(getline(fd2,buf))
    {
        cout << buf << endl;
    }
    fd2.close();
}

int main()
{
        test01();
        return 0;
}