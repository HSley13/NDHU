#include <iostream>
#include <cmath>

class Fraction
{
private:
    int numerator, denominator;

public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int n, int m) : numerator(n)
    {
        if (m == 0)
            throw "divided by zero";
        denominator = m;
    }

    int getNumerator() const { return numerator; }

    int getDenominator() const { return denominator; }

    void setNumerator(int n) { numerator = n; }

    void setDenominator(int m)
    {
        if (m == 0)
            throw "divided by zero";
        denominator = m;
    }

    friend std::ostream &operator<<(std::ostream &out, const Fraction &f)
    {
        if (f.denominator != 1)
            out << "[" << f.numerator << "/" << f.denominator << "]";
        else
            out << f.numerator;
        return out;
    }
};

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

void simplify(int &num, int &deno)
{
    if (!num)
    {
        deno = 1;
        return;
    }

    int common_divisor = gcd(abs(num), abs(deno));

    num /= common_divisor;
    deno /= common_divisor;
}

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    int num = (f1.getNumerator() * f2.getDenominator()) + (f1.getDenominator() * f2.getNumerator());

    int deno = f1.getDenominator() * f2.getDenominator();

    simplify(num, deno);

    return Fraction(num, deno);
}

Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    int num = (f1.getNumerator() * f2.getDenominator()) - (f1.getDenominator() * f2.getNumerator());

    int deno = f1.getDenominator() * f2.getDenominator();

    simplify(num, deno);

    return Fraction(num, deno);
}

bool operator==(const Fraction &f1, const Fraction &f2)
{
    return (f1.getNumerator() / f1.getDenominator()) == (f2.getNumerator() / f2.getDenominator());
}
