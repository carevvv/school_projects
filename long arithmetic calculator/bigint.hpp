#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <cstdint>
#include <iostream>

class BigInt {
private:
    std::vector<int32_t> digits;
public:
    BigInt();
    BigInt(int value);
    BigInt(const BigInt &x);
    BigInt(const std::string &value);

    void negate();
    void print_result() const;

    BigInt operator+(const BigInt &x) const;
    BigInt operator-(const BigInt &x) const;
    BigInt operator*(const BigInt &x) const;
    BigInt operator+() const;
    BigInt operator-() const;
    bool operator>(const BigInt &x) const;
    bool operator<(const BigInt &x) const;
    bool operator>=(const BigInt &x) const;
    bool operator<=(const BigInt &x) const;
    bool operator==(const BigInt &x) const;
    bool operator!= (const BigInt &x) const;

    friend std::ostream & operator<<(std::ostream &out, const BigInt &x);
};


#endif
