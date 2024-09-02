#pragma once
#include <iostream>
using namespace std;

class point
{
public:
    void setpx(int px);
    void setpy(int py);
    int getpx();
    int getpy();

private:
    int p_x;
    int p_y;
};
