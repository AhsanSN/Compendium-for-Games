#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;

struct Point
{
    Point():x(0),y(0) {}
    Point(float x,float y):x(x),y(y) {}
    Point(const Point& toCopy):x(toCopy.x),y(toCopy.y) {}
    Point& operator=(const Point& toAssign)
    {
        x=(toAssign.x);
        y=(toAssign.y);
        return *this;
    }
    float x;
    float y;
    Point operator++(int)//post increment operator, shifts current point to the left by one brick unit
    {
        x+=48;
        return *this;
    }
    Point operator++()//pre increment operator, shifts current point down by one brick unit
    {
        y+=18;
        return *this;
    }
};
ostream& operator <<(ostream& a,const Point& toPrint);      // for saving


#endif // POINT_H
