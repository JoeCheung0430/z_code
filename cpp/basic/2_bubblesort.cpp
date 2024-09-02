#include <iostream>
using namespace std;

void bubble(int *array, int size);

void bubble(int* array,int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1;j++)
        {
            if(array[j]>array[j+1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int array[10] = {1, 3, 2, 5, 4, 7, 6, 8, 9, 0};
    int size = sizeof(array) / sizeof(array[0]);
    cout <<"size:"<< size << endl;
    bubble(array, size);
    for (int i = 0; i < size;i++)
    {
        cout << array[i] <<" ";
    }
    cout << endl;
    system("pause");
    return 0;
}