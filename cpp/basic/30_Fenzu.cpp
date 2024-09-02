/*
- 公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
- 员工信息有: 姓名  工资组成；部门分为：策划、美术、研发
- 随机给10名员工分配部门和工资
- 通过multimap进行信息的插入  key(部门编号) value(员工)
- 分部门显示员工信息
*/

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <ctime>

#define Cehua 0
#define Meishu 1
#define Yanfa 2

class person
{
public:
    person(string name,int salary)
    {
        this->m_name = name;
        this->m_salary = salary;
    }
    string m_name;
    int m_salary;
};

void CreatorWorker(vector<person> &v)
{
    string nameseed = "ABCDEFGHIJ";
    for (int i = 0; i < 10; i++)
    {
        string name = "Worker ";
        name += nameseed[i];
        int salary = rand() % 10000 + 10000;
        person p(name, salary);
        v.push_back(p);
    }
#if 0
    for (vector<person>::const_iterator it = v.begin(); it != v.end();it++)
    {
        cout << "name:" << it->m_name << "  " << "salary:" << it->m_salary << endl;
    }
    cout << endl;
#endif
}

void SetWorker(vector<person> &v,multimap<int,person> &m)
{
    for (vector<person>::const_iterator it = v.begin();it!=v.end();it++)
    {
        int id = rand() % 3;
        m.insert(make_pair(id, *it));
    }
}

void ShowWorker(const multimap<int,person> &m)
{
    cout << "策划部门成员" << endl;
    multimap<int, person>::const_iterator pos=m.find(Cehua);
    int key = m.count(Cehua);
    int num=0;
    for (; pos != m.end() && num<key; pos++,num++)
    {
        cout << "name:" << pos->second.m_name << "  " << "salary:" << pos->second.m_salary << endl;
    }
    cout << "----------------------------" << endl;
    cout << "美术部门成员" << endl;
    pos=m.find(Meishu);
    key = m.count(Meishu);
    num=0;
    for (; pos != m.end() && num<key; pos++,num++)
    {
        cout << "name:" << pos->second.m_name << "  " << "salary:" << pos->second.m_salary << endl;
    }
    cout << "研发部门成员" << endl;
    pos=m.find(Yanfa);
    key = m.count(Yanfa);
    num=0;
    for (; pos != m.end() && num<key; pos++,num++)
    {
        cout << "name:" << pos->second.m_name << "  " << "salary:" << pos->second.m_salary << endl;
    }
}

void syswork()
{
    srand((unsigned int)time(NULL));
    vector<person> vworker;
    multimap<int, person> mworker;
    
    CreatorWorker(vworker);
    SetWorker(vworker,mworker);
    ShowWorker(mworker);
}

int main()
{
    syswork();
    return 0;
}