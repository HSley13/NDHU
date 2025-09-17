#include <iostream>
#include <vector>

const std::string num = "0123456789ABCDEF";

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
private:
    Digit value[1000];

    int count = 0;

public:
    Integer();

    Integer(std::string n);

    void displayInBase(int base) const;
};

Integer::Integer()
{
    count++;
    value[0].setDigit(0);
}

Integer::Integer(std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            value[i].setDigit(str[i] - '0');
            count++;
        }
        else
            break;
    }
}

void Integer::displayInBase(int base) const
{
    std::vector<int> ans, tmp1, tmp2;

    for (int i = 0; i < count; i++)
        tmp1.push_back(value[i].getDigit());

    while (tmp1.size() > 1 || tmp1[tmp1.size() - 1] != 0)
    {
        tmp2.clear();

        int tmp = 0;

        for (int i = 0; i < tmp1.size(); i++)
        {
            tmp *= 10;
            tmp += tmp1[i];

            if (tmp2.size() == 0 && tmp / base == 0)
                continue;

            tmp2.push_back(tmp / base);
            tmp %= base;
        }

        ans.push_back(tmp);
        tmp1 = tmp2;
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        std::cout << num[ans[i]];
}

int main(void)
{
    std::string in;

    std::cin >> in;

    Integer k(in);

    for (int i = 2; i <= 16; i++)
    {
        k.displayInBase(i);
        std::cout << std::endl;
    }
}