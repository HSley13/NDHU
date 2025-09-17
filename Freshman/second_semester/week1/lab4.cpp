#include <iostream>

class find_velocity
{
private:
    double distance, time;

public:
    find_velocity(double distance, double time) : distance(distance), time(time) {}

    void get_velocity();
};

void find_velocity::get_velocity()
{
    std::cout << distance / time << std::endl;
}

int main(void)
{
    double km, hours;

    std::cin >> km >> hours;

    find_velocity velocity(km, hours);

    velocity.get_velocity();
}