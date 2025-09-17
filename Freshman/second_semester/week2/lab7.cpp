#include <iostream>
#include <cmath>

// The class Point should be deleted/commented before uploading to OJ cause it's not necessary, thus OJ will judge it as a compile error

class Point
{
private:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }
};

class Segment
{
private:
    Point start, end;

public:
    Segment(Point start, Point end) : start(start), end(end) {}

    double length()
    {
        return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2));
    }

    Point getEnd(int index);
};

Point Segment::getEnd(int index)
{
    if (!index)
        return start;

    else
        return end;
}