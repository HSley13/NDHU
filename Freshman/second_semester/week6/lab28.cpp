#include <iostream>
#include <cmath>

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

    float getLength() const { return point1.getDistance(point2); }
};