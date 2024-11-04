#ifndef COMPLEXINT_HPP
#define COMPLEXINT_HPP

#include <iostream>

class ComplexInt {
private:
    double re, im; // re - real, im - imaginary
public:
    ComplexInt(double a = 0, double b = 0);
    ComplexInt(const ComplexInt &value);
    ComplexInt(const std::string &value);

    ComplexInt operator+(const ComplexInt &x) const;
    ComplexInt operator-(const ComplexInt &x) const;
    ComplexInt operator*(const ComplexInt &x) const;
    ComplexInt operator/(const ComplexInt &x) const;
    ComplexInt operator+() const;
    ComplexInt operator-() const;

    bool operator==(const ComplexInt &x) const;
    bool operator!=(const ComplexInt &x) const;

    friend std::ostream & operator<<(std::ostream &out, const ComplexInt &x);
};


#endif 
