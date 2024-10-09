#include "bigint.hpp"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>


BigInt::BigInt(int a) {
    this->digits = std::vector<int32_t>(MAX_DIGITS, 0);
    if (a < 0) {
        this->digits[0] = -a;
        this->complement();
    } else {
        this->digits[0] = a;
    }
}

BigInt::BigInt(const BigInt &x) {
    this->digits = x.digits;
}


void BigInt::complement() {
    int64_t carry = 1;
    for (size_t i = 0; i < this->MAX_DIGITS; ++i) {
        digits[i] = this->BASE - this->digits[i];
    }
    
    for (size_t i = 0; i < this->MAX_DIGITS; ++i) {
        int64_t sum = static_cast<int64_t>(this->digits[i]) + carry;

        if (sum > this->BASE) {
            this->digits[i] = sum - this->BASE - 1;
            carry = 1;
        } else {
            this->digits[i] = sum;
            carry = 0;
        } 

        if (carry == 0) {
            break;
        }
    }
}


BigInt BigInt::add(const BigInt &a) const {
    BigInt result;

    int carry = 0;
    for (size_t i = 0; i < MAX_DIGITS; ++i) {
        int this_digit_block = (i < this->digits.size()) ? this->digits[i] : 0;
        int a_digit_block = (i < a.digits.size()) ? a.digits[i] : 0;

        int64_t sum = static_cast<int64_t>(this_digit_block) + static_cast<int64_t>(a_digit_block) + carry;
        if (sum > INT32_MAX) {
            result.digits[i] = sum - INT32_MAX - 1;
            carry = 1;
        } else {
            result.digits[i] = sum;
            carry = 0;
        }
    }
    /*if (carry > 0) {
        result.digits.push_back(carry);
    }*/
    return result; 
}


BigInt BigInt::sub(const BigInt &a) const {
    BigInt result = a;
    result.complement();
    return this->add(result);
}


void BigInt::print_result(const BigInt &x) const {
    long long sum = 0;
    for (int i = x.digits.size() - 1; i >= 0; --i) {
        std::cout << static_cast<long long>(x.digits[i]) << "|"; 
    }
    std::cout << std::endl;
}


int main(void) {
    BigInt a = INT32_MIN;
    BigInt b = INT32_MAX;
    BigInt d = a.add(b);
    d.print_result(d);
    return 0;
}