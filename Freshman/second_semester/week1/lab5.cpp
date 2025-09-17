#include <iostream>

class segments
{
private:
    int a1, a2, b1, b2;

public:
    segments(int a1, int a2, int b1, int b2) : a1(a1), a2(a2), b1(b1), b2(b2) {}

    void overlay_or_not();
};

void segments::overlay_or_not()
{
    if (a1 > a2)
    {
        int temp = a1;
        a1 = a2;
        a2 = temp;
    }

    if (b1 > b2)
    {
        int temp = b1;
        b1 = b2;
        b2 = temp;
    }

    if (b1 >= a2 || b2 <= a1)
        std::cout << "no overlay";
    else
        std::cout << "overlay";
}

int main(void)
{
    int a1, a2, b1, b2;
    std::cin >> a1 >> a2 >> b1 >> b2;

    segments result(a1, a2, b1, b2);

    result.overlay_or_not();
}
