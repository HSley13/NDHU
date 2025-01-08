#include <stdexcept>

int calculate(char o1, char o2, int i1, int i2, int i3) {
    if ((o1 == '*' || o1 == '+' || o1 == '-' || o1 == '/') && (o2 == '*' || o2 == '+' || o2 == '-' || o2 == '/')) {
        int intermediate;
        switch (o2) {
        case '*':
            intermediate = i2 * i3;
            break;
        case '+':
            intermediate = i2 + i3;
            break;
        case '-':
            intermediate = i2 - i3;
            break;
        case '/':
            if (i3 == 0)
                throw std::runtime_error("Division by zero in second operator");
            intermediate = i2 / i3;
            break;
        default:
            throw std::runtime_error("Invalid operator");
        }

        switch (o1) {
        case '*':
            return i1 * intermediate;
        case '+':
            return i1 + intermediate;
        case '-':
            return i1 - intermediate;
        case '/':
            if (intermediate == 0) {
                throw std::runtime_error("Division by zero in first operator");
            }
            return i1 / intermediate;
        default:
            throw std::runtime_error("Invalid operator");
        }
    } else {
        throw std::runtime_error("Invalid operator input");
    }
}
