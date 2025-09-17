#include <iostream>

class Anagram : public std::string
{
private:
    std::string _a = "";

public:
    Anagram(std::string a);

    bool operator==(const Anagram &str) const;
};

Anagram::Anagram(std::string a)
{
    for (const char &c : a)
    {
        if (std::isalpha(c))
            _a += std::tolower(c);
    }
}

bool Anagram::operator==(const Anagram &str) const
{
    int tmp[26] = {0};

    if (this->_a.length() != str._a.length())
        return false;

    for (const char &c : this->_a)
        tmp[c - 'a']++;

    for (const char &c : str._a)
    {
        if (!tmp[c - 'a'])
            return false;
    }

    return true;
};

int main(void)
{
    std::string buf;

    std::getline(std::cin, buf);
    Anagram a1(buf);

    std::getline(std::cin, buf);
    Anagram a2(buf);

    std::cout << (a1 == a2) << std::endl;
    std::cout << (a2 == a1) << std::endl;
}