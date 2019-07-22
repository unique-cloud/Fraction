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

// Fraction::Fraction(double decimal)
// {
//     // count effective numbers on integer part
//     double cp = decimal;
//     int len = 0;
//     while (cp >= 1 || cp <= -1)
//     {
//         len++;
//         cp /= 10;
//     }
//     // out of range
//     if (len > effective_num)
//         throw std::invalid_argument("Decimal value is too large!");

//     // count factor that scales numerator up to maximum effective numbers
//     int factor = 1;
//     for (int i = 0; i < effective_num - len; ++i)
//         factor *= 10;

//     Fraction temp(decimal * factor, factor);
//     swap(temp);
// }

Fraction::Fraction(double decimal)
{
    // best rational approximation approach based on continued fractions
    // convergent has
    // numerator:
    // next term in CF × the previous numerator + the numerator before that
    // denominator:
    // next term in CF × the previous denominator + the denominator before that

    int sign = (decimal < 0) ? -1 : 1;
    decimal *= sign;

    if (decimal > int_max)
        throw std::invalid_argument("Decimal value is too large!");

    int pre_pre_n = 0, pre_pre_d = 1, pre_n = 1, pre_d = 0;
    double cp = decimal;
    while (true)
    {
        int i = static_cast<int>(cp);
        long long n = pre_pre_n + i * static_cast<long long>(pre_n);
        long long d = pre_pre_d + i * static_cast<long long>(pre_d);
        if (n > int_max || d > int_max)
            break;

        pre_pre_n = pre_n;
        pre_pre_d = pre_d;
        pre_n = n;
        pre_d = d;

        cp = 1 / (cp - i);
        if (cp > int_max)
            break;
    }

    Fraction temp(sign * pre_n, pre_d);
    swap(temp);
}

Fraction::Fraction(Fraction &&rhs) noexcept
{
    numerator_ = std::move(rhs.numerator_);
    denominator_ = std::move(rhs.denominator_);
    rhs.reset();
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

void Fraction::reset()
{
    numerator_ = 0;
    denominator_ = 1;
}

long long Fraction::gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    int sign = b;

    while (a %= b)
        std::swap(a, b);

    return (sign ^ b) >= 0 ? b : -b;
}

long long Fraction::lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;

    return abs(static_cast<long long>(a) * b / gcd(a, b));
}

void Fraction::reduction()
{
    auto div = gcd(numerator_, denominator_);
    numerator_ /= div;
    denominator_ /= div;
}

Fraction::operator std::string() const
{
    if (denominator_ == 1)
        return std::to_string(numerator_);
    else
        return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

Fraction::operator double() const
{
    return static_cast<double>(numerator_) / denominator_;
}

Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
    auto n = static_cast<long long>(lhs.numerator()) * rhs.denominator() + static_cast<long long>(lhs.denominator()) * rhs.numerator();
    auto d = static_cast<long long>(lhs.denominator() * rhs.denominator());

    auto div = Fraction::gcd(n, d);
    n /= div;
    d /= div;

    if (n > int_max || d > int_max)
        throw std::overflow_error("Fraction arithmetic overflow!");
    if (n < int_min)
        throw std::underflow_error("Fraction arithmetic underflow!");

    return Fraction(static_cast<int>(n), static_cast<int>(d));
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    auto div1 = Fraction::gcd(lhs.numerator(), rhs.denominator());
    auto div2 = Fraction::gcd(lhs.denominator(), rhs.numerator());

    auto n = static_cast<long long>(lhs.numerator()) / div1 * (rhs.numerator() / div2);
    auto d = static_cast<long long>(lhs.denominator()) / div2 * (rhs.denominator() / div1);

    if (n > int_max || d > int_max)
        throw std::overflow_error("Fraction arithmetic overflow!");
    if (n < int_min)
        throw std::underflow_error("Fraction arithmetic underflow!");

    return Fraction(static_cast<int>(n), static_cast<int>(d));
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    if (rhs.numerator() == int_min)
        return lhs + Fraction(int_max, rhs.denominator()) + Fraction(1, rhs.denominator());
    else
        return lhs + Fraction(rhs.numerator() * -1, rhs.denominator());
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    if (rhs.numerator() == 0)
        throw std::overflow_error("Divide by zero!");

    return lhs * Fraction(rhs.denominator(), rhs.numerator());
}

bool operator==(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.numerator() == rhs.numerator() && lhs.denominator() == rhs.denominator();
}

bool operator!=(const Fraction &lhs, const Fraction &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Fraction &lhs, const Fraction &rhs)
{
    return static_cast<long long>(lhs.numerator()) * rhs.denominator() < static_cast<long long>(lhs.denominator() * rhs.numerator());
}

bool operator>(const Fraction &lhs, const Fraction &rhs)
{
    return static_cast<long long>(lhs.numerator()) * rhs.denominator() > static_cast<long long>(lhs.denominator() * rhs.numerator());
}

std::ostream &operator<<(std::ostream &o, const Fraction &rhs)
{
    return o << std::string(rhs);
}
