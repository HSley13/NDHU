#include <iostream>
#include <vector>
#include <algorithm>

const std::string num = "0123456789";

class Digit
{
private:
    int digit;

public:
    Digit(int d) : digit(d % 10) {}

    Digit() { digit = 0; }

    void setDigit(int d) { digit = d % 10; }

    int getDigit() const { return digit; }
};

class Integer
{
    Digit value[1000];

    bool sign = 0;

    int count = 0;

public:
    Integer();

    Integer(std::string n);

    Integer addition(const Integer &b) const;

    Integer subtraction(const Integer &b) const;

    void display();
};

Integer::Integer()
{
    count++;
    value[0].setDigit(0);
}

Integer::Integer(std::string n)
{
    std::reverse(n.begin(), n.end());

    for (int i = 0; i < n.length(); i++)
    {
        if (n[i] >= '0' && n[i] <= '9')
        {
            value[i].setDigit(n[i] - '0');
            count++;
        }

        if (n[i] == '-')
            sign = 1;
    }
}

Integer Integer::addition(const Integer &b) const
{
    std::string ans = "";
    int len = std::max(count, b.count), carry = 0;

    for (int i = 0; i < len; i++)
    {
        int tmp = value[i].getDigit() + b.value[i].getDigit() + carry;
        carry = 0;

        if (tmp >= 10)
        {
            tmp -= 10;
            carry = 1;
        }

        ans.push_back(num[tmp]);
    }

    if (carry)
        ans.push_back('1');

    std::reverse(ans.begin(), ans.end());

    return Integer(ans);
}

Integer Integer::subtraction(const Integer &b) const
{
    std::string ans = "";

    bool negative = 0, carry = 0;

    if (count < b.count)
        negative = 1;

    else if (count == b.count)
    {
        for (int i = count - 1; i >= 0; i--)
        {
            if (value[i].getDigit() > b.value[i].getDigit())
                break;

            if (value[i].getDigit() < b.value[i].getDigit())
            {
                negative = 1;
                break;
            }
        }
    }

    int len = std::max(count, b.count), tmp;

    for (int i = 0; i < len; i++)
    {
        if (!negative)
            tmp = value[i].getDigit() - b.value[i].getDigit() - carry;
        else
            tmp = b.value[i].getDigit() - value[i].getDigit() - carry;

        carry = 0;

        if (tmp < 0)
        {
            tmp += 10;
            carry = 1;
        }

        ans.push_back(num[tmp]);
    }

    if (negative)
        ans.push_back('-');

    std::reverse(ans.begin(), ans.end());

    return Integer(ans);
};

void Integer::display()
{
    bool is_non_zero = 0;

    if (sign)
        std::cout << "-";

    for (int i = count - 1; i >= 0; i--)
    {
        if (value[i].getDigit() != 0 || is_non_zero || i == 0)
        {
            std::cout << num[value[i].getDigit()];
            is_non_zero = 1;
        }
    }
}

int main(void)
{
    std::string a, b;
    std::cin >> a >> b;

    Integer num_1(a), num_2(b);

    num_1.addition(num_2).display();
    std::cout << std::endl;

    num_2.addition(num_1).display();
    std::cout << std::endl;

    num_1.subtraction(num_2).display();
    std::cout << std::endl;

    num_2.subtraction(num_1).display();
    std::cout << std::endl;
}
