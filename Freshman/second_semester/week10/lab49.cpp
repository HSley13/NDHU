#include <cmath>
#include <iostream>

class PrimeOrEmirp {
    int _num;

  public:
    PrimeOrEmirp(int n);

    bool is_prime(int n);

    int reverse(int n);

    bool is_emirp(int n);
};

PrimeOrEmirp::PrimeOrEmirp(int num) : _num(num) {
    if (!is_prime(_num))
        std::cout << _num << " is not prime." << std::endl;

    else if (!is_emirp(_num))
        std::cout << _num << " is prime." << std::endl;

    else
        std::cout << _num << " is emirp." << std::endl;
};

bool PrimeOrEmirp::is_prime(int n) {
    if (n <= 1)
        return false;

    for (int i = 2; i < std::sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int PrimeOrEmirp::reverse(int n) {
    int r = 0;
    int temp = n;
    while (temp) {
        r = r * 10 + temp % 10;
        temp /= 10;
    }
    return r;
}

bool PrimeOrEmirp::is_emirp(int n) {
    if (!is_prime(n))
        return false;

    int rev = reverse(n);
    return rev != n && is_prime(rev);
}

int main(void) {
    int test_case;

    while (std::cin >> test_case)
        PrimeOrEmirp test(test_case);
}
