#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
    float _x;
    float _y;

public:
    Point() : _x(0), _y(0) {}
    Point(float x, float y) : _x(x), _y(y) {}

    float getX() const { return _x; }
    void setX(float x) { _x = x; }

    float getY() const { return _y; }
    void setY(float y) { _y = y; }

    void printPoint() const { std::cout << "(" << _x << ", " << _y << ")"; }

    float getDistance(const Point &point_2) const { return std::sqrt(static_cast<float>(std::pow(this->_x - point_2._x, 2)) + static_cast<float>(std::pow(this->_y - point_2._y, 2))); }
};

class Segment
{
private:
    Point point1;
    Point point2;

public:
    Segment() : point1(Point()), point2(Point()) {}
    Segment(const Point &point_1, const Point &point_2) : point1(point_1), point2(point_2) {}

    Point &getStart() { return point1; };
    Point &getEnd() { return point2; };

    float getLength() const { return point1.getDistance(point2); }

    friend std::ostream &operator<<(std::ostream &out, const Segment &segment);
};

std::ostream &operator<<(std::ostream &out, const Segment &segment)
{
    segment.point1.printPoint();
    segment.point2.printPoint();
    out << " -> ";

    return out;
}

class Shape
{

private:
    Segment seg[10];
    int edgeCount;

public:
    Shape() : edgeCount(0){};
    Shape(Segment *segments, int edge_count);

    virtual float getArea() = 0;
    float getPerimeter();

    Segment &getSeg(int index) { return seg[index]; }
};

float Shape::getPerimeter()
{
    float perimeter = 0;
    for (int i = 0; i < edgeCount; ++i)
        perimeter += getSeg(i).getLength();

    return perimeter;
};

Shape::Shape(Segment *segments, int edge_count) : edgeCount(edge_count)
{
    Point *first = &(segments[0].getStart());
    Point *last = &(segments[edgeCount - 1].getEnd());

    if (*first != *last)
        throw std::invalid_argument("invalid_argument");

    for (int i = 0; i < edge_count; ++i)
        seg[i] = segments[i];
};