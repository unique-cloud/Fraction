#ifndef _FRACTION_FRACTION_H_
#define _FRACTION_FRACTION_H_

#include <iostream>

// this value is chose due to range of type int
const int effective_num = 9;

class Fraction
{
    int numerator_ = 0;
    int denominator_ = 1;

public:
    Fraction(int numerator = 0, int denominator = 1);
    Fraction(double decimal);
    Fraction(float decimal) : Fraction((double)decimal) {}
    Fraction(const Fraction &rhs) : numerator_(rhs.numerator_), denominator_(rhs.denominator_) {}
    Fraction(Fraction &&rhs) noexcept;
    ~Fraction() { clear(); }

    // copy and swap idiom
    Fraction &operator=(Fraction rhs);
    void swap(Fraction &rhs);

    void clear();
    void reduction();
    int gcd(int a, int b) const;

    int numerator() const { return numerator_; }
    int denominator() const { return denominator_; }

    operator std::string() const;
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