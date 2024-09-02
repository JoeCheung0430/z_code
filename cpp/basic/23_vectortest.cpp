#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

void printflist(int num)
{
    cout << num << endl;
}

void test01()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    #if 0
    for_each(v.begin(), v.end(), printflist);
    #endif
    
    #if 1
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
    #endif
}

class Person{
public:
    Person(string name,int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    string m_name;
    int m_age;
};

void test02()
{
    vector<Person> v2;
    Person p1("a", 1);
    Person p2("b", 2);
    Person p3("c", 3);
    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);
    for (vector<Person>::iterator it2 = v2.begin(); it2 != v2.end();it2++)
    {
        cout << it2->m_name << " " << it2->m_age << endl;
    }
}

int main()
{
    //test01();
    test02();
    return 0;
}