/*------------------------------------------------------------
案例描述：将Person自定义数据类型进行排序，Person中属性有姓名、年龄、身高
排序规则：按照年龄进行升序，如果年龄相同按照身高进行降序
------------------------------------------------------------*/

#include <iostream>
using namespace std;
#include <string>
#include <list>

class Person
{
public:
    Person(string name,int age,int height)
    {
        this->m_name = name;
        this->m_age = age;
        this->m_height = height;
    }
    string m_name;
    int m_age;
    int m_height;
};

bool comparePerson(Person &p1,Person &p2)
{
    if(p1.m_age==p2.m_age)
    {
        return p1.m_height > p2.m_height;
    }
    else{
        return p1.m_age < p2.m_age;
    }
}

void list_test()
{
    list<Person> l;
    Person p1("刘备", 35, 175);
    Person p2("曹操", 45 , 180);
	Person p3("孙权", 40 , 170);
	Person p4("赵云", 25 , 190);
	Person p5("张飞", 35 , 160);
	Person p6("关羽", 35 , 200);

    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);
    l.push_back(p4);
    l.push_back(p5);
    l.push_back(p6);

    for (list<Person>::iterator it = l.begin(); it != l.end(); it++)
    {
        cout << "Name:" << it->m_name << "  " << "Age:" << it->m_age << "  " << "Height:" << it->m_height << endl;
    }

    cout << "---------------排序后----------------" << endl;
    l.sort(comparePerson);
    for (list<Person>::iterator it = l.begin(); it != l.end(); it++)
    {
        cout << "Name:" << it->m_name << "  " << "Age:" << it->m_age << "  " << "Height:" << it->m_height << endl;
    }
    cout << endl;
}

int main()
{
    list_test();
    return 0;
}