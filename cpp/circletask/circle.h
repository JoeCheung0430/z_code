#pragma once
#include <iostream>
using namespace std;
#include "point.h"

class circle{
public:
    void setcenter(point center);
    void setr(int r);
    point getcenter();
    int getr();

private:
    int c_r;
    point c_center;
};