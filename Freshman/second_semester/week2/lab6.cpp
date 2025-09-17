#include <iostream>
#include <vector>

class point
{
private:
    double x, y;

public:
    point(double x, double y) : x(x), y(y) {}

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }
};

int main(void)
{
    int n;
    std::cin >> n;

    std::vector<point> points;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        std::cin >> x >> y;

        point p(x, y);
        points.push_back(p);
    }

    for (int i = 0; i < n; i++)
        std::cout << "(" << points[i].getX() << ", " << points[i].getY() << ")" << std::endl;
}
