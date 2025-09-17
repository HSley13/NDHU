#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class instructions
{
private:
    std::string _cmd, _p1, _p2, _p3;

public:
    instructions(std::string cmd, std::string p1, std::string p2, std::string p3);

    void reg_translate(std::string a);

    void op_translate(std::string a);

    void shamt() { std::cout << "00000"; }

    void func_translate(std::string a);

    void dec_to_bin(int a);
};

instructions::instructions(std::string cmd, std::string p1, std::string p2, std::string p3) : _cmd(cmd), _p1(p1), _p2(p2), _p3(p3)
{
    if (_cmd == "addi")
    {
        op_translate(_cmd);

        reg_translate(_p2);
        reg_translate(_p1);
        reg_translate(_p3);
    }
    else
    {
        op_translate(_cmd);

        reg_translate(_p2);
        reg_translate(_p3);
        reg_translate(_p1);

        shamt();

        func_translate(_cmd);
    }
}

void instructions::reg_translate(std::string a)
{
    std::string tmp = a.substr(0, 3);

    if (tmp == "$t0")
        std::cout << "01000";

    else if (tmp == "$t1")
        std::cout << "01001";

    else if (tmp == "$t2")
        std::cout << "01010";

    else if (tmp == "$t3")
        std::cout << "01011";

    else if (tmp == "$t4")
        std::cout << "01100";

    else if (tmp == "$t5")
        std::cout << "01101";

    else if (tmp == "$t6")
        std::cout << "01110";

    else if (tmp == "$t7")
        std::cout << "01111";

    else
        dec_to_bin(std::stoi(a));
}

void instructions::op_translate(std::string a)
{
    if (a == "add")
        std::cout << "000000";

    else if (a == "sub")
        std::cout << "000000";

    else if (a == "or")
        std::cout << "000000";

    else if (a == "and")
        std::cout << "000000";

    else if (a == "addi")
        std::cout << "001000";
}

void instructions::func_translate(std::string a)
{
    if (a == "add")
        std::cout << "100000";

    else if (a == "sub")
        std::cout << "100010";

    else if (a == "or")
        std::cout << "100101";

    else if (a == "and")
        std::cout << "100100";
}

void instructions::dec_to_bin(int a)
{
    long long digit = 0, ans = 0;

    while (a)
    {
        ans += (a % 2) * (std::pow(10, digit));
        a /= 2;
        digit++;
    }

    if (!digit)
        digit = 1;

    for (int i = 0; i < (16 - digit); i++)
        std::cout << "0";

    std::cout << ans;
}

int main(void)
{
    std::string cmd, p1, p2, p3;

    while (std::cin >> cmd >> p1 >> p2 >> p3)
    {
        instructions a(cmd, p1, p2, p3);
        std::cout << std::endl;
    }
}
