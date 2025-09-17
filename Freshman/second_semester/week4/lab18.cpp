#include <iostream>
#include <cmath>

class Fraction
{
private:
    int numerator, denominator;

    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    void simplify();

public:
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int num, int deno) : numerator(num), denominator(deno) { simplify(); }

    int get_numerator() const { return numerator; }

    int get_denominator() const { return denominator; }

    void set_numerator(int num) { numerator = num; }

    void set_denominator(int deno)
    {
        if (!deno)
            return;

        denominator = deno;
    }

    void display() const;

    Fraction operator+(const Fraction &other) const;

    Fraction operator-(const Fraction &other) const;

    Fraction operator*(const Fraction &other) const;

    Fraction operator/(const Fraction &other) const;

    Fraction &operator=(const Fraction &other);

    friend std::ostream &operator<<(std::ostream &os, const Fraction &fraction);
};

void Fraction::simplify()
{
    if (!numerator)
    {
        denominator = 1;
        return;
    }

    int common_divisor = gcd(abs(numerator), abs(denominator));

    numerator /= common_divisor;
    denominator /= common_divisor;
}

void Fraction::display() const
{
    if (denominator == 1)
        std::cout << numerator;

    else
        std::cout << "(" << numerator << "/" << denominator << ")";
}

Fraction Fraction::operator+(const Fraction &other) const
{
    int num = (this->numerator * other.denominator) + (other.numerator * this->denominator);

    int deno = this->denominator * other.denominator;

    return Fraction(num, deno);
}

Fraction Fraction::operator-(const Fraction &other) const
{
    int num = (this->numerator * other.denominator) - (other.numerator * this->denominator);

    int deno = this->denominator * other.denominator;

    return Fraction(num, deno);
}

Fraction Fraction::operator*(const Fraction &other) const
{
    int num = numerator * other.numerator;

    int denom = denominator * other.denominator;

    return Fraction(num, denom);
}

Fraction Fraction::operator/(const Fraction &other) const
{
    int num = this->numerator * other.denominator;

    int deno = this->denominator * other.numerator;

    return Fraction(num, deno);
}

Fraction &Fraction::operator=(const Fraction &other)
{
    if (this != &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    if (f.denominator == 1)
        out << f.numerator;

    else
        out << "(" << f.numerator << "/" << f.denominator << ")";

    return out;
}
