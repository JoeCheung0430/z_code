#include <iostream>
using namespace std;
#include <stack>

void stack_init()
{
    stack<int> sta;
    for (int i = 10; i < 50;i+=10)
    {
        sta.push(i);
    }
    cout << "stack的大小为:" << sta.size() << endl;
    while(!sta.empty())
    {
        cout << sta.top() << " ";
        sta.pop();
    }
    cout << endl;
    cout << "stack的大小为:" << sta.size() << endl;
}

int main()
{
    stack_init();
    return 0;
}