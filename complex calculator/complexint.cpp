#include "complexint.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>


ComplexInt::ComplexInt(double a, double b) {
    this->re = a;
    this->im = b;
}


ComplexInt::ComplexInt(const ComplexInt &x) {
    this->re = x.re;
    this->im = x.im;
}


ComplexInt
ComplexInt::operator+(const ComplexInt &x) const {
    return ComplexInt(this->re + x.re, this->im + x.im);
}


ComplexInt
ComplexInt::operator-(const ComplexInt &x) const {
    return ComplexInt(this->re - x.re, this->im - x.im);
}


ComplexInt 
ComplexInt::operator*(const ComplexInt &x) const {
    return ComplexInt(this->re * x.re - this->im * x.im, this->re * x.im + this->im * x.re);
}


ComplexInt 
ComplexInt::operator/(const ComplexInt &x) const {
    if (pow(x.re, 2) + pow(x.im, 2) == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        exit(1);
    }
    return ComplexInt((this->re * x.re + this->im * x.im) / (pow(x.re, 2) + pow(x.im, 2)), (this->im * x.re - this->re * x.im) / (pow(x.re, 2) + pow(x.im, 2)));
}


ComplexInt 
ComplexInt::operator+() const {
    return *this;
}


ComplexInt 
ComplexInt::operator-() const {
    return ComplexInt(-re, -im);
}


bool 
ComplexInt::operator==(const ComplexInt &x) const {
    return this->re == x.re && this->im == x.im;
}


bool
ComplexInt::operator!=(const ComplexInt &x) const {
    return !(*this == x);
}   


std::ostream & operator<<(std::ostream &out, const ComplexInt &x) {
    if (x.im < 0) {
        out << x.re << " - " << -x.im << "i";
        return out;
    }
    out << x.re << " + " << x.im << "i";
    return out;
}


int
main (void) {
    ComplexInt a;
    ComplexInt b(12, 2);
    ComplexInt c = a + b;
    ComplexInt d = a - b;
    ComplexInt e = a * b;
    ComplexInt f = a / b;
    bool g = (a == b);
    bool h = (a != b);
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;
    std::cout << h << std::endl;
    return 0;
}