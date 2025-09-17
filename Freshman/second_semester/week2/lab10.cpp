#include <iostream>
#include <string>

class four
{
private:
    int n;

public:
    four(int n) : n(n) {}

    std::string found_or_not();
};

std::string four::found_or_not()
{
    while (n)
    {
        if (n % 10 == 4)
            return "Yes";

        n /= 10;
    }

    return "No";
}

int main(void)
{
    int plate_num;

    std::cin >> plate_num;

    if (plate_num > 0)
    {
        four p(plate_num);

        std::cout << p.found_or_not() << std::endl;
    }
}