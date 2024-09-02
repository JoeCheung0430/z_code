#include <iostream>
using namespace std;
#include <map>

void printstl(const map<int,int> &m)
{
    for (map<int, int>::const_iterator it = m.begin(); it != m.end();it++)
    {
        cout << "key:" << it->first << "  " << "value:" << it->second << endl;
    }
    cout << endl;
}

void map_test01()
{
    map<int, int> m;
    m.insert(pair<int, int>(1,10));
    m.insert(pair<int, int>(3,30));
    m.insert(pair<int, int>(2,20));
    m.insert(pair<int, int>(4,40));
    m.insert(pair<int, int>(5,50));
    printstl(m);
}

int main()
{
    map_test01();
    return 0;
}
