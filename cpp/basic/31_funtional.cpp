/* 
template<class T> T plus<T>`               //加法仿函数
template<class T> T minus<T>`              //减法仿函数
template<class T> T multiplies<T>`         //乘法仿函数
template<class T> T divides<T>`            //除法仿函数
template<class T> T modulus<T>`            //取模仿函数
template<class T> T negate<T>`             //取反仿函数

template<class T> bool equal_to<T>`                //等于
template<class T> bool not_equal_to<T>`            //不等于
template<class T> bool greater<T>`                 //大于
template<class T> bool greater_equal<T>`           //大于等于
template<class T> bool less<T>`                    //小于
template<class T> bool less_equal<T>`              //小于等于

template<class T> bool logical_and<T>`              //逻辑与
template<class T> bool logical_or<T>`               //逻辑或
template<class T> bool logical_not<T>`              //逻辑非
*/

#include <iostream>
using namespace std;
#include <functional>
#include <algorithm>
#include <vector>

void plus_test()
{
    plus<int> p;
    cout << p(1, 1) << endl;
}

void negate_test()
{
    negate<int> n;
    cout << n(10) << endl;
}

void minus_test()
{
    minus<int>m;
    cout << m(10, 1) << endl;
}

void modulus_test()
{
    modulus<int> m2;
    cout << m2(4,3) << endl;
}

void test01()
{
    vector<int> p;
    p.push_back(10);
    p.push_back(40);
    p.push_back(20);
    p.push_back(30);

    sort(p.begin(), p.end(), greater<int>());
    for (vector<int>::iterator it = p.begin(); it != p.end();it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void test02()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    for (vector<bool>::iterator it = v.begin(); it != v.end();it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
    vector<bool> v2;
    v2.resize(v.size());
    transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
    for (vector<bool>::iterator it = v2.begin(); it != v2.end();it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

int main()
{
    plus_test();
    negate_test();
    minus_test();
    modulus_test();
    test01();
    test02();
    return 0;
}