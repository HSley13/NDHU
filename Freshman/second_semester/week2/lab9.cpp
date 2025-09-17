#include <iostream>
#include <cmath>

class find_total
{
private:
    const double price = 1.2;
    double distance;

public:
    find_total(double distance) : distance(distance) {}

    double total_price();
};

double find_total::total_price()
{
    double total;

    if (distance <= 200)
        total = (distance * price);

    else if (distance > 200)
        total = (200 * price) + (((distance - 200) * price) * 0.75);

    return total;
}

int main(void)
{
    double distance;
    std::cin >> distance;

    find_total result(distance);

    std::cout << round(result.total_price()) << std::endl;
}
