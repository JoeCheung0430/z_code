#include <iostream>
using namespace std;

class building
{
    friend void test();

public:
    building (){
        sittingroom = "客厅";
        bedroom = "卧室";
    }
    string sittingroom;
private:
    string bedroom;
};

void test()
{
    building b1;
    cout << "visit" << b1.sittingroom << endl;
    cout << "visit" << b1.bedroom << endl;
}

int main()
{
    test();
    return 0;
}