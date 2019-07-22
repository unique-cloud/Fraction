// Author: Xiaorui Tang
// Date: 07/12/2019

// This is a Fraction class implemented in C++that supports the following operations:
// addition, subtraction, multiplication, division, equality/non-equality, greater than/less than, and display.

#ifndef _FRACTION_FRACTION_H_
#define _FRACTION_FRACTION_H_

#include <iostream>
#include <limits>

// this value is chosen due to the range of type int
// const int effective_num = 9;
const int int_max = std::numeric_limits<int>::max();
const int int_min = std::numeric_limits<int>::min();

class Fraction
{
    int numerator_ = 0;
    int denominator_ = 1;

    void reset();
    void reduction();

public:
    Fraction(int numerator = 0, int denominator = 1);
    Fraction(double decimalx);
    // Fraction(float decimal) : Fraction((double)decimal) {}
    Fraction(const Fraction &rhs) : numerator_(rhs.numerator_), denominator_(rhs.denominator_) {}
    Fraction(Fraction &&rhs) noexcept;
    ~Fraction() {}

    // copy and swap idiom
    Fraction &operator=(Fraction rhs);
    void swap(Fraction &rhs);

    // use euclidean algorithm to get the greatest common divisors of two integers
    // the sign of result will always same with b unless b == 0
    // gcd(0, k) == gcd(k, 0) == k, gcd(0, 0) == 0
    static int gcd(int a, int b);
    static long long lcm(int a, int b);

    int numerator() const { return numerator_; }
    int denominator() const { return denominator_; }

    operator std::string() const;
    explicit operator double() const;
};

Fraction operator+(const Fraction &lhs, const Fraction &rhs);
Fraction operator-(const Fraction &lhs, const Fraction &rhs);
Fraction operator*(const Fraction &lhs, const Fraction &rhs);
Fraction operator/(const Fraction &lhs, const Fraction &rhs);

bool operator==(const Fraction &lhs, const Fraction &rhs);
bool operator!=(const Fraction &lhs, const Fraction &rhs);
bool operator<(const Fraction &lhs, const Fraction &rhs);
bool operator>(const Fraction &lhs, const Fraction &rhs);

std::ostream &operator<<(std::ostream &o, const Fraction &rhs);

#endif