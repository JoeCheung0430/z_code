#include <iostream>
using namespace std;

class cube{
public:
    void setlwh(int l,int w,int h)
    {
        c_l = l;
        c_w = w;
        c_h = h;
    }
    int getlwh(char num)
    {
        if(num=='l'){
            return c_l;
        }
        if(num=='w'){
            return c_w;
        }
        if(num=='h'){
            return c_h;
        }
        cout << "error" << endl;
        return 0;
    }

    int calculateC()
    {
        return 2*c_l * c_w + 2*c_l * c_h + 2*c_w * c_l;
    }

    int calculateV()
    {
        return c_l * c_w * c_h;
    }

    bool compare(cube &c)
    {
        if (c_l == c.getlwh('l')&&c_w == c.getlwh('w')&&c_h == c.getlwh('h'))
        {
            return true;
        }
        return false;
    }

private:
    int c_l;
    int c_w;
    int c_h;
};

int main()
{
    cube c1;
    c1.setlwh(10, 10, 10);
    cout << "C=" << c1.calculateC() << endl;
    cout << "V=" << c1.calculateV() << endl;
    cube c2;
    c2.setlwh(20, 20, 20);
    cube c3;
    c3.setlwh(10, 10, 10);
    bool ret = c1.compare(c3);
    if(ret)
    {
        cout << "same" << endl;
    }
    return 0;
}