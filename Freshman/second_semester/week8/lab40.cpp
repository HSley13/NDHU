#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define MAX_N_COORD 100

class Coord {
    int x, y;

  public:
    Coord() : x(0), y(0) {};
    Coord(int _x, int _y) : x(_x), y(_y) {};
    Coord(const Coord &c) : x(c.x), y(c.y) {};
    void setX(int new_x) { x = new_x; };
    int getX() { return x; }
    void setY(int newY) { y = newY; };
    int getY() { return y; }

    bool operator<(const Coord &other) const { return (x < other.x || (x == other.x && y < other.y)); }

    bool operator>(const Coord &other) const { return (x > other.x || (x == other.x && y > other.y)); }

    Coord &operator=(const Coord &other) {
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    friend double get_distance(Coord &start, Coord &end) { return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2)); };

    friend std::ostream &operator<<(std::ostream &out, const Coord &c) {
        out << "(" << c.x << ", " << c.y << ")";
        return out;
    }
};

std::vector<Coord> input_coordinates(int n, int *y_max) {
    std::vector<Coord> coords;
    int x, y;

    coords.push_back(Coord(0, 0));

    while (--n >= 0) {
        std::cin >> x >> y;
        *y_max = (y > *y_max) ? y : *y_max;

        coords.push_back(Coord(x, y));
    }

    std::sort(coords.begin(), coords.end(), std::greater<Coord>());

    return coords;
};

double get_distance(std::vector<Coord> &coords, int y_max) {
    int temp_y_max = 0;
    double sum = 0;

    Coord a, b, c;

    for (int i = 1; i < coords.size() && temp_y_max != y_max; i++) {
        if (coords[i].getY() > temp_y_max) {

            c = coords[i];
            b = coords[i - 1];

            a = Coord(c.getX(), b.getY());

            sum += get_distance(c, b) - sqrt(pow(temp_y_max - b.getY(), 2) * (1 + pow(get_distance(a, b), 2) / pow(get_distance(a, c), 2)));

            temp_y_max = coords[i].getY();
        }
    }

    return sum;
}

int main(void) {
    int test_cases = 0, N = 0, y_max = 0;
    size_t i;
    double d;

    std::cin >> test_cases;
    test_cases++;

    while (--test_cases) {
        std::cin >> N;

        std::vector<Coord> coords = input_coordinates(N, &y_max);
        d = get_distance(coords, y_max);

        printf("%.2lf\n", d);
    }
}
