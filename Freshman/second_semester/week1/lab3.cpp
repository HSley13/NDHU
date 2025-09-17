#include <iostream>
#include <cmath>

class Triangle
{
public:
    Point p1, p2, p3;

    Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {}

    double distance(Point start, Point end);

    double perimeter();
};

double Triangle::distance(Point start, Point end)
{
    return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2));
}

double Triangle::perimeter()
{
    double side_1 = distance(p1, p2);
    double side_2 = distance(p2, p3);
    double side_3 = distance(p3, p1);

    return side_1 + side_2 + side_3;
}

int main(void)
{
    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        double x1, y1, x2, y2, x3, y3;

        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        Point p1;
        p1.setX(x1);
        p1.setY(y1);

        Point p2;
        p2.setX(x2);
        p2.setY(y2);

        Point p3;
        p3.setX(x3);
        p3.setY(y3);

        Triangle triangle(p1, p2, p3);
        std::cout << triangle.perimeter() << std::endl;
    }
}