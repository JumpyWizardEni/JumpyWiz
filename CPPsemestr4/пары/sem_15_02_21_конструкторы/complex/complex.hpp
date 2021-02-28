#include <iostream>

class Complex {
private:
    double re;
    double im;
public:
    Complex(double re2, double im2 = 0);
    friend Complex operator +(const Complex & firstNumber, const Complex & secNumber);
    Complex operator -(const Complex & secNumber);
    Complex operator *(const Complex & secNumber);
    Complex operator /(const Complex & secNumber);
    Complex & operator = (const Complex & secNumber);
    friend std::ostream & operator << (std::ostream &, const Complex &);
};