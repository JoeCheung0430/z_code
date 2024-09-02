#include <iostream>
using namespace std;
#include "point.h"
#include "circle.h"

void distance(circle &c,point &p)
{
    int distance =
        (c.getcenter().getpx() - p.getpx()) * (c.getcenter().getpx() - p.getpx()) +
        (c.getcenter().getpy() - p.getpy()) * (c.getcenter().getpy() - p.getpy());
    int r2 = c.getr() * c.getr();
    if(distance==r2)
    {
        cout << "点在圆上" << endl;
    }
    else if(distance > r2)
    {
        cout << "点在圆外" << endl;
    }
    else if(distance < r2)
    {
        cout << "点在圆内" << endl;
    }
}

int main()
{
    circle c1;
    point center;
    point p;
    center.setpx(10);
    center.setpy(0);
    c1.setcenter(center);
    c1.setr(10);
    p.setpx(10);
    p.setpy(10);
    distance(c1, p);
    return 0;
}