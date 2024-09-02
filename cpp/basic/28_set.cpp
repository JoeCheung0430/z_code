#include <iostream>
using namespace std;
#include <set>

class mycompare
{
public:
    bool operator()(const int &a,const int &b) const
    {
        return a > b;
    }
};

void printstl(const set<int>&st)
{
    for (set<int>::const_iterator it = st.begin(); it != st.end();it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void set_test()
{
    set<int> st;
    st.insert(10);
    st.insert(40);
    st.insert(20);
    st.insert(30);
    printstl(st);
    set<int>::iterator findnum = st.find(60);
    if(findnum!=st.end())
    {
        cout << "num=" << *findnum << endl;
    }
    else{
        cout << "find error" << endl;
    }
    int num = st.count(30);
    cout << "count=" << num << endl;
}

void set_test02()
{
    set<int,mycompare> s2;
    s2.insert(10);
    s2.insert(30);
    s2.insert(40);
    s2.insert(20);
    for (set<int,mycompare>::iterator it = s2.begin(); it != s2.end();it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    set_test();
    set_test02();
    return 0;
}