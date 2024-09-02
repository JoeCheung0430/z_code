#include <iostream>
#include <string>
using namespace std;

class Student{
public:
    string s_name;
    string s_id;
    void show()
    {
        cout << "学生的姓名:" << s_name << " " << "学生的学号:" << s_id << endl;
    }
};

int main()
{
    Student std1;
    std1.s_name = "Joe";
    std1.s_id = "202111612133";
    std1.show();
    return 0;
}