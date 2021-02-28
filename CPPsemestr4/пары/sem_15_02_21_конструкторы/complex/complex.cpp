#include "complex.hpp"


Complex::Complex(double re2, double im2) {
    this->re = re2;
    this->im = im2;
}

Complex operator +(const Complex & firstNumber, const Complex & secNumber){
    return Complex(firstNumber.re + secNumber.re, firstNumber.im + secNumber.im);
}

Complex Complex::operator -(const Complex & secNumber){
    return Complex(re - secNumber.re, im - secNumber.im);
}

Complex Complex::operator *(const Complex & secNumber){
    return Complex(re*secNumber.re - im*secNumber.im, re*secNumber.im + im*secNumber.re);
}

Complex Complex::operator /(const Complex & secNumber){
    return Complex((re*secNumber.re + im*secNumber.im) / (secNumber.re * secNumber.re + secNumber.im + secNumber.im), 
                    (im*secNumber.re - re*secNumber.im) / (secNumber.re * secNumber.re + secNumber.im + secNumber.im));
}

Complex & Complex::operator = (const Complex & secNumber){
    re = secNumber.re;
    im = secNumber.im;
    return *this;
}   

std::ostream & operator << (std::ostream & out, const Complex & number) {
    return out << "Re: " << number.re << ", Im: " << number.im << std::endl;
}