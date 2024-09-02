#include <iostream>
using namespace std;
int main()
{
    int result[20];
    int endcount[20];
    int count[20] = {82000,88000,73900,82000,70800,70500,75400,82000,71800,70000,74600,75000};
    for (int i = 0; i < 14;i++)
    {
        result[i] = count[i] * 0.05;
        //cout << result[i] << endl;
        endcount[i] = count[i] - result[i];
        cout << endcount[i] << endl;
    }
    return 0;
}
