#include <iostream>
using namespace std;
#include <deque>
#include <algorithm>
void printdeque(const deque<int> &d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end();it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test01()
{
    deque<int> d;
    for (int i = 0; i < 9;i++)
    {
        d.push_back(i);
    }
    cout << "d的数据为:" << endl;
    printdeque(d);
    deque<int> d2(d);
    cout << "d2的数据为:" << endl;
    printdeque(d2);
    cout << "d2的大小为:" << d2.size() << endl;
    if(d2.empty())
    {
        cout << "d2为空" << endl;
    }else
    {
        cout << "d2不为空" << endl;
    }
    d2.resize(15, 'a');
    printdeque(d2);
    cout << "d2的大小为:" << d2.size() << endl;
}

void test02()
{
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(10);
    d.push_front(20);
    printdeque(d);
    d.pop_back();
    printdeque(d);
    d.insert(d.begin(), 100);
    printdeque(d);
    d.erase(d.begin());
    printdeque(d);
    d.erase(d.end()-1);
    printdeque(d);
    deque<int>::iterator it = d.begin();
    it++;
    d.erase(it);
    printdeque(d);
    d.clear();
    printdeque(d);
}

void test03()
{
    deque<int> d;
    d.push_back(3);
    d.push_back(2);
    d.push_back(1);
    d.push_front(100);
    d.push_front(200);
    printdeque(d);
    sort(d.begin(),d.end());
    printdeque(d);
}

int main()
{
    //test01();
    //test02();
    test03();
    return 0;
}