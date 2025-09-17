#include <iostream>

class CycleCount {
    int _num1, _num2;

  public:
    CycleCount() : _num1(0), _num2(0) {};
    CycleCount(int a, int b) : _num1(a < b ? a : b), _num2(b > a ? b : a) {};

    int calculate_cycle(int n);

    int get_max_cycle();
};

int CycleCount::get_max_cycle() {
    int current_max = 0, cycle = 0;
    for (int i = this->_num1; i <= this->_num2; i++) {
        cycle = calculate_cycle(i);
        current_max = (cycle > current_max) ? cycle : current_max;
    }

    return current_max;
};

int CycleCount::calculate_cycle(int n) {
    if (n == 1)
        return 1;
    else if (n % 2)
        return calculate_cycle((3 * n) + 1) + 1;
    else
        return calculate_cycle(n / 2) + 1;
}

int main(void) {
    CycleCount cycle;
    int num1, num2;

    while (std::cin >> num1 >> num2) {
        cycle = CycleCount(num1, num2);

        std::cout << num1 << " " << num2 << " " << cycle.get_max_cycle() << std::endl;
    }
}
