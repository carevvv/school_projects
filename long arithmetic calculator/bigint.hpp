// bigint.hpp
#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <cstdint>
#include <iostream>

class BigInt {
public:
    std::vector<int32_t> digits;

    BigInt();
    BigInt(int64_t value);
    BigInt(const BigInt &x);

    BigInt add(const BigInt &a) const;
    
    BigInt sub(const BigInt &a) const;
    void print_result() const;
    void negate();
    void normalize();

    friend std::ostream & operator<<(std::ostream &out, const BigInt &x);
};


#endif
