#include <iostream>
using namespace std;

template <typename T>
void myswap(T &a,T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void mysort(T arr[],int len)
{
    for (int i = 0; i < len;i++)
    {
        int max = i;
        for (int j = i + 1; j < len; j++)
        {
            if(arr[j]>arr[max])
            {
                max = j;
            }
        }
        if(max!=i)
        {
            myswap(arr[max], arr[i]);
        }
    }
}

template <typename T>
void printsort(T arr[],int len)
{
    for (int i = 0; i < len;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void test()
{
    char arr1[5] = {'e', 'b', 'a', 'c', 'd'};
    int arr2[5] = {1, 2, 3, 4, 5};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    mysort(arr1, len1);
    printsort(arr1, len1);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    mysort(arr2, len2);
    printsort(arr2, len2);
}

int main()
{
    test();
    return 0;
}