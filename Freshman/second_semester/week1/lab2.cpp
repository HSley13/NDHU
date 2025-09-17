#include <iostream>
#include <cmath>

class point
{
private:
    double x, y;

public:
    point(double x, double y) : x(x), y(y) {}

    double getX()
    {
        return this->x;
    }

    double getY()
    {
        return this->y;
    }
};

class Segment
{
public:
    point start;
    point end;

    Segment(point start, point end) : start(start), end(end){};

    double distance();
};

double Segment::distance()
{
    return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2));
}

int main(void)
{
    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        double start_X, start_Y, end_X, end_Y;

        std::cin >> end_X >> end_Y >> start_X >> start_Y;

        point start(start_X, start_Y);
        point end(end_X, end_Y);

        Segment segment(start, end);

        std::cout << segment.distance() << std::endl;
    }
}
