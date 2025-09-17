#include <iostream>
#include <vector>
#include <algorithm>

class numbers
{
private:
    std::vector<int> list;

    int n;

public:
    void insert();

    int reverse_integer(int a);

    bool check(int a);

    void next();
};

void numbers::insert()
{
    std::cin >> n;
    list.resize(n);

    for (int i = 0; i < n; i++)
        std::cin >> list[i];
}

int numbers::reverse_integer(int a)
{
    std::string tmp = std::to_string(a);

    std::reverse(tmp.begin(), tmp.end());

    a = std::stoi(tmp);

    return a;
}

bool numbers::check(int a)
{
    std::string check = std::to_string(a);

    std::string check2 = check;

    std::reverse(check2.begin(), check2.end());

    return !check.compare(check2);
}

void numbers::next()
{
    for (int i = 0; i < n; i++)
    {
        int count = 0;

        while (count == 0 || !check(list[i]))
        {
            list[i] += reverse_integer(list[i]);
            count++;
        }

        std::cout << count << " " << list[i] << std::endl;
    }
}

int main(void)
{
    numbers a;

    a.insert();

    a.next();
}