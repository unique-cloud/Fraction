// Author: Xiaorui Tang
// Date: 07/12/2019

#include "Fraction.h"

Fraction::Fraction(int numerator, int denominator)
{
    if (denominator == 0)
        throw std::invalid_argument("Denominator can't be 0!");

    this->numerator_ = numerator;
    this->denominator_ = denominator;
    reduction();
}

Fraction::Fraction(double decimal)
{
    // extract sign
    int sign = (decimal < 0) ? -1 : 1;
    decimal *= sign;

    // count effective numbers on integer part
    int integer = (int)decimal;
    int len = 0;
    if (integer != 0)
        len++;
    while (integer > 10)
    {
        integer /= 10;
        len++;
    }

    // move decimal point to contain all effective numbers
    int factor = 1;
    for (int i = 0; i < effective_num - len; ++i)
        factor *= 10;

    Fraction temp(sign * decimal * factor, factor);
    swap(temp);
}

Fraction::Fraction(Fraction &&rhs) noexcept
{
    numerator_ = std::move(rhs.numerator_);
    denominator_ = std::move(rhs.denominator_);
    rhs.clear();
}

Fraction &Fraction::operator=(Fraction rhs)
{
    swap(rhs);
    return *this;
}

void Fraction::swap(Fraction &rhs)
{
    std::swap(numerator_, rhs.numerator_);
    std::swap(denominator_, rhs.denominator_);
}

void Fraction::clear()
{
    numerator_ = 0;
    denominator_ = 1;
}

int Fraction::gcd(int a, int b) const
{
    // eculidean algorithm
    while (a %= b)
        std::swap(a, b);

    return b;
}

void Fraction::reduction()
{
    if (this->numerator_ == 0)
    {   
        this->denominator_ = 1;
        return;
    }

    int sign = 1;
    if (this->numerator_ < 0)
    {
        sign *= -1;
        this->numerator_ *= -1;
    }
    if (this->denominator_ < 0)
    {
        sign *= -1;
        this->denominator_ *= -1;
    }

    auto div = gcd(this->numerator_, this->denominator_);
    this->numerator_ /= div;
    this->denominator_ /= div;

    // always associate sign with numerator
    this->numerator_ *= sign;
}

Fraction::operator std::string() const
{
    if (denominator_ == 1)
        return std::to_string(numerator_);
    else
        return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator() + lhs.denominator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator() - lhs.denominator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
}

bool operator==(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.numerator() * rhs.denominator() == lhs.denominator() * rhs.numerator();
}

bool operator!=(const Fraction &lhs, const Fraction &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.numerator() * rhs.denominator() < lhs.denominator() * rhs.numerator();
}

bool operator>(const Fraction &lhs, const Fraction &rhs)
{
    return !(lhs < rhs) && !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &o, const Fraction &rhs)
{
    return o << std::string(rhs);
}
