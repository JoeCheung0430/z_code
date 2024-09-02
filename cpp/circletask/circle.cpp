#include "circle.h"

void circle::setcenter(point center)
{
    c_center = center;
}

void circle::setr(int r)
{
    c_r = r;
}

point circle::getcenter()
{
    return c_center;
}

int circle::getr()
{
    return c_r;
}