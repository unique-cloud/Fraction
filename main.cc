// Author: Xiaorui Tang
// Date: 07/12/2019

#include "Fraction.h"
#include "UTest.h"

#include <sstream>
using namespace std;

void unitTest()
{
    auto ut = new UTest("Fraction");

    Fraction *a, *b, *c, *d;

    /***************************** test constructor *******************************/
    a = new Fraction();      // 0
    b = new Fraction(-5);    // -5
    c = new Fraction(2, -3); // -2/3

    // default constructor
    ut->test("default constructor", a->numerator() == 0 && a->denominator() == 1);
    ut->test("default constructor", b->numerator() == -5 && b->denominator() == 1);
    ut->test("default constructor", c->numerator() == -2 && c->denominator() == 3);

    // copy constrcutor
    d = new Fraction(*c);
    ut->test("copy constructor", d->numerator() == -2 && d->denominator() == 3);

    // move constrcutor
    *d = move(*b);
    ut->test("move constructor", d->numerator() == -5 && d->denominator() == 1);
    ut->test("move constructor", b->numerator() == 0 && b->denominator() == 1);

    // assignment operator
    *d = *a;
    ut->test("assignment operator", d->numerator() == 0 && d->denominator() == 1);
    *d = std::move(*c);
    ut->test("assignment operator", d->numerator() == -2 && d->denominator() == 3);
    ut->test("assignment operator", c->numerator() == 0 && c->denominator() == 1);

    delete a;
    delete b;
    delete c;
    delete d;

    /****************************** test arithmetic *******************************/
    a = new Fraction(5);     // 5
    b = new Fraction(2, 3);  // 2/3
    c = new Fraction(3, -6); // -1/2
    d = new Fraction();

    // addition
    *d = *a + *b;
    ut->test("addition", d->numerator() == 17 && d->denominator() == 3);
    *d = *b + *c;
    ut->test("addition", d->numerator() == 1 && d->denominator() == 6);
    *d = 2 + *b;
    ut->test("addition", d->numerator() == 8 && d->denominator() == 3);

    // subtraction
    *d = *a - *b;
    ut->test("subtraction", d->numerator() == 13 && d->denominator() == 3);
    *d = *b - *c;
    ut->test("subtraction", d->numerator() == 7 && d->denominator() == 6);
    *d = 2 - *b;
    ut->test("subtraction", d->numerator() == 4 && d->denominator() == 3);

    // multiplication
    *d = *a * *b;
    ut->test("multiplication", d->numerator() == 10 && d->denominator() == 3);
    *d = *b * *c;
    ut->test("multiplication", d->numerator() == -1 && d->denominator() == 3);
    *d = -2 * *c;
    ut->test("multiplication", d->numerator() == 1 && d->denominator() == 1);

    // division
    *d = *a / *b;
    ut->test("division", d->numerator() == 15 && d->denominator() == 2);
    *d = *b / *c;
    ut->test("division", d->numerator() == -4 && d->denominator() == 3);
    *d = 2 / *c;
    ut->test("division", d->numerator() == -4 && d->denominator() == 1);

    delete a;
    delete b;
    delete c;
    delete d;

    /******************************** test relation *******************************/
    a = new Fraction(3, 5);  // 3/5
    b = new Fraction(6, 10); // 3/5
    c = new Fraction(-2, 3); // -2/3

    // equality/non-equality
    ut->test("equality", *a == *b);
    ut->test("non-equality", *a != *c);

    // greater than/less than
    ut->test("greater than", *b > *c);
    ut->test("less than", *c < *a);
    ut->test("greater than", *b > 0);
    ut->test("less than", 0 < -1 * *c);

    delete a;
    delete b;
    delete c;

    /********************************* test reduction *****************************/
    a = new Fraction(6, 10);  // 3/5
    b = new Fraction(10, -4); // -5/2
    c = new Fraction();

    ut->test("reduction", a->numerator() == 3 && a->denominator() == 5);
    ut->test("reduction", b->numerator() == -5 && b->denominator() == 2);

    *c = *a + *b;
    ut->test("reduction", c->numerator() == -19 && c->denominator() == 10);
    *c = *a - *b;
    ut->test("reduction", c->numerator() == 31 && c->denominator() == 10);
    *c = *a * *b;
    ut->test("reduction", c->numerator() == -3 && c->denominator() == 2);
    *c = *a / *b;
    ut->test("reduction", c->numerator() == -6 && c->denominator() == 25);

    delete a;
    delete b;
    delete c;

    /********************************* test decimal ********************************/
    a = new Fraction(0.6);
    b = new Fraction(-2.8);
    c = new Fraction(12.125);
    d = new Fraction(0.0);

    ut->test("reduction", a->numerator() == 3 & a->denominator() == 5);
    ut->test("reduction", b->numerator() == -14 & b->denominator() == 5);
    ut->test("reduction", c->numerator() == 97 & c->denominator() == 8);
    ut->test("reduction", d->numerator() == 0 & d->denominator() == 1);

    delete a;
    delete b;
    delete c;
    delete d;

    /********************************* test display ********************************/
    a = new Fraction(5);     // 5
    b = new Fraction(6, 10); // 2/5
    c = new Fraction(-3, 6); // -1/2
    d = new Fraction(4, -2); // -2

    stringstream o;
    o << *a;
    ut->test("display", o.str() == "5");
    o.str(string());
    o << *b;
    ut->test("display", o.str() == "3/5");
    o.str(string());
    o << *c;
    ut->test("display", o.str() == "-1/2");
    o.str(string());
    o << *d;
    ut->test("display", o.str() == "-2");

    delete a;
    delete b;
    delete c;
    delete d;

    /********************************* test result ********************************/
    ut->report();

    delete ut;
}

int main()
{
    // comment this line to turn off test code
    unitTest();

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    cout << "This is a Fraction class implemented in C++, "
         << "including functionalities such as addition, subtraction, "
         << "multiplication, division, equality/non-equality, "
         << "greater than/less than, reduction, conversion from decimal number and display. "
         << "Here are some examples: "
         << endl;

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    Fraction a(6, 10);
    Fraction b(10, -4);
    Fraction c = a;

    cout << "Fraction a is: " << a << endl;
    cout << "Fraction b is: " << b << endl;
    cout << "Fraction c is a copy of a: " << c << endl;
    cout << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << endl;

    cout << "a < b is " << (a < b ? "true" : "false") << endl;
    cout << "b < c is " << (b < c ? "true" : "false") << endl;
    cout << "a == c is " << (a == c ? "true" : "false") << endl;
    cout << "b != c is " << (b != c ? "true" : "false") << endl;

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    cout << "You may notice that the result is reduced to lowest terms automatically. "
         << endl
         << endl;

    cout << "But be careful that currently, we use type int to store numerator and denominator, "
         << "and there is no protection if the numerator or denominator is over the range of type int. "
         << endl
         << endl;

    cout << "We also provide a choice that you can create a fraction object using dicimal values, like "
         << endl;

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    Fraction d(12.125);
    Fraction e(-0.45);
    Fraction f(0.0);
    cout << "Create fraction from 12.125 is: " << d << endl;
    cout << "Create fraction from -0.45 is: " << e << endl;
    cout << "Create fraction from 0.0 is: " << f << endl;

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    cout << "But as the way we use to transfrom dicimal to fraction is relatively naive for now, "
         << "we actually could only keep 9 effective numbers which is also bounded by the range of type int. "
         << "If it is not enough, we can simply improve this to 18 effective numbers by "
         << "using long long int to store the numerator and denominator. "
         << endl
         << endl;

    cout << "By the way, move semantic is supported to improve performance by avoiding some unnecessary copies. "
         << endl;

    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;

    return 0;
}
