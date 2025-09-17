#include <iostream>
#include <cstring>

class PokerCard
{

private:
    std::string suit;
    int face;

public:
    PokerCard(std::string s, int f) : suit(s), face(f) {}

    int getFace() { return face; };
    std::string getSuit() { return suit; }

    friend std::ostream &operator<<(std::ostream &out, const PokerCard &p)
    {
        out << "[" << p.face << " of " << p.suit << "]";
        return out;
    }

    bool operator>(PokerCard &b);

    bool operator<(PokerCard &b);

    bool operator==(PokerCard &b);
};

bool PokerCard::operator>(PokerCard &b)
{
    if (b.getFace() != getFace())
    {
        if (this->getFace() == 1)
            return true;

        else if (b.getFace() == 1)
            return false;

        return this->getFace() > b.getFace();
    }
    else
        return getSuit()[0] > b.getSuit()[0];
}

bool PokerCard::operator<(PokerCard &b)
{
    if (*this == b)
        return false;
    else
        return !(*this > b);
}

bool PokerCard::operator==(PokerCard &b)
{
    return (this->getFace() == b.getFace() && this->getSuit() == b.getSuit());
}