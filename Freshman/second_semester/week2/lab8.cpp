#include <iostream>
#include <math.h>

// Only upload the class Path, its contructor and the member functon same_or_not to OJ (that's what they asked) otherwise it will be a compile error

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

class Path
{
public:
    Path(Segment *segments, int length);

    bool same_or_not(Point a, Point b);
};

bool Path::same_or_not(Point a, Point b)
{
    return (a.getX() == b.getX() && a.getY() == b.getY());
}

Path::Path(Segment *segments, int length)
{
    double sum = 0;
    int i = 0;

    for (; i < length - 1; i++)
    {
        if (!same_or_not(segments[i].getEnd(1), segments[i + 1].getEnd(0)))
            break;

        sum += segments[i].length();
    }

    if (i == length - 1)
    {
        sum += segments[i].length();

        double length = (same_or_not(segments[i].getEnd(1), segments[0].getEnd(0))) ? -1 : sum;

        std::cout << length << std::endl;
    }
    else
        std::cout << "-1" << std::endl;
}
