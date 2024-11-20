#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <vector>
#include <deque>
#include <iostream>

template <typename T>
class Calculator {
protected:
    virtual ~Calculator() = default;
public:
    virtual T operator+(const T& other) const = 0;
    virtual T operator-(const T& other) const = 0;
    virtual T operator*(const T& other) const = 0;
    virtual T operator/(const T& other) const = 0;

    virtual bool operator<(const T& other) const = 0;
    virtual bool operator>(const T& other) const = 0;
    virtual bool operator==(const T& other) const = 0;
    virtual bool operator!=(const T& other) const = 0;
    virtual bool operator<=(const T& other) const = 0;
    virtual bool operator>=(const T& other) const = 0;

    virtual T operator+(double other) const = 0;
    virtual T operator-(double other) const = 0;
    virtual T operator*(double other) const = 0;
    virtual T operator/(double other) const = 0;
    virtual T operator^(double other) const = 0;

    virtual T operator+() const = 0;
    virtual T operator-() const = 0;

    virtual T calculate(const std::string& expression) = 0;
};


class Complex : public Calculator<Complex> {
private:
    double re; 
    double im; 
    bool arePairs(char open, char close);
    bool brackets(const std::deque<char>& inputDeque);
    int get_priority(char op);
    std::deque<std::string> infix_to_postfix(const std::deque<char>& input_deq);
    Complex evaluate_postfix(const std::deque<std::string>& postfix);

public:
    Complex(double re = 0.0, double im = 0.0);
    Complex(const Complex& other);
    Complex(const std::string& s);

    Complex operator+(const Complex& x) const override;
    Complex operator+(double x) const override;
    Complex operator-(const Complex& x) const override;
    Complex operator-(double x) const override;
    Complex operator*(const Complex& x) const override;
    Complex operator*(double x) const override;
    Complex operator/(const Complex& x) const override;
    Complex operator/(double x) const override;

    Complex operator+() const override;
    Complex operator-() const override;

    Complex operator^(double x) const override;

    bool operator==(const Complex& x) const override;
    bool operator!=(const Complex& x) const override;
    bool operator>(const Complex& x) const override;
    bool operator<(const Complex& x) const override;
    bool operator>=(const Complex& x) const override;
    bool operator<=(const Complex& x) const override;

    friend std::ostream& operator<<(std::ostream& out, const Complex& x);
    Complex calculate(const std::string& expression) override;
};


class BigInt : public Calculator<BigInt> {
private:
    std::vector<int32_t> digits; 
    bool arePairs(char open, char close);
    bool isHexDigit(char c);
    bool brackets(const std::deque<char>& inputDeque);
    int get_priority(char op);
    std::deque<std::string> infix_to_postfix(const std::deque<char>& input_deq);
    BigInt evaluate_postfix(const std::deque<std::string>& postfix);
public:
    BigInt();
    BigInt(int value);
    BigInt(const BigInt& other);
    BigInt(const std::string& value);

    void negate();
    void print_result() const;

    BigInt operator+(const BigInt &x) const override;
    BigInt operator-(const BigInt &x) const override;
    BigInt operator*(const BigInt &x) const override;
    BigInt operator/(const BigInt &x) const override;

    BigInt operator+(double x) const override;
    BigInt operator-(double x) const override;
    BigInt operator*(double x) const override;
    BigInt operator/(double x) const override;
    BigInt operator^(double x) const override;

    BigInt operator+() const override;
    BigInt operator-() const override;

    bool operator>(const BigInt &x) const override;
    bool operator<(const BigInt &x) const override;
    bool operator>=(const BigInt &x) const override;
    bool operator<=(const BigInt &x) const override;
    bool operator==(const BigInt &x) const override;
    bool operator!= (const BigInt &x) const override;

    BigInt calculate(const std::string& expression) override;

    friend std::ostream& operator<<(std::ostream& out, const BigInt& x);
};

#endif 