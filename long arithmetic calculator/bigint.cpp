#include "bigint.hpp"
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>



BigInt::BigInt() {
    digits.push_back(0);
}

BigInt::BigInt(int64_t value) {
    while (value != 0 && value != -1) {
        int32_t word = static_cast<int32_t>(value & 0xFFFFFFFF);
        digits.push_back(word);
        value >>= 32;
    }
    if (value == -1) {
        digits.push_back(-1);
    } else if (digits.empty()) {
        digits.push_back(0);
    }
}

BigInt::BigInt(const BigInt &x) {
    digits = x.digits;
}


BigInt BigInt::add(const BigInt &a) const {
    BigInt result;
    size_t maxSize = std::max(this->digits.size(), a.digits.size());
    result.digits.resize(maxSize, 0);

    int64_t carry = 0;
    bool thisneg = (this->digits.back() & 0x80000000);
    bool aneg = (a.digits.back() & 0x80000000); 

    for (size_t i = 0; i < maxSize; ++i) {
        int64_t class_digit = (i < this->digits.size()) ? static_cast<uint32_t>(this->digits[i]) : 0;
        int64_t a_digit = (i < a.digits.size()) ? static_cast<uint32_t>(a.digits[i]) : 0;

        int64_t sum = class_digit + a_digit + carry;

        result.digits[i] = static_cast<int32_t>(sum & 0xFFFFFFFF);

        carry = (sum >> 32) & 0x1;
    }
    
    if ((!thisneg && !aneg) && result.digits.back() < 0) {
        std::cout << "thisneg && aneg" << std::endl;
        result.digits.push_back(0);
    }

    if (thisneg != aneg) {
        std::cout << "thisneg != aneg" << std::endl;
        if (thisneg && !aneg) {
            if (result.digits.back() & 0x80000000) {
                if (carry != 0) {
                    result.digits.push_back(-1);
                }
            }
        } else if (!thisneg && aneg) {
            if (!(result.digits.back() & 0x80000000) && carry != 0) {
                result.digits.push_back(0);
            }
        }
    } else if (carry != 0) {
        std:: cout << "carry != 0" << std::endl;
        if (thisneg) {
            result.digits.push_back(-1);
        } else {
            result.digits.push_back(0);
        }
    }
    return result;
}




void BigInt::negate() {
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] = ~digits[i];
    }

    int64_t carry = 1;
    for (size_t i = 0; i < digits.size(); ++i) {
        uint64_t sum = (static_cast<uint32_t>(digits[i]) & 0xFFFFFFFFULL) + carry;
        digits[i] = static_cast<int32_t>(sum & 0xFFFFFFFF);
        carry = sum >> 32;
        if (carry == 0) {
            break;
        }
    }

    if (carry != 0) {
        digits.push_back(static_cast<int32_t>(carry));
    }
}

BigInt BigInt::sub(const BigInt &a) const {
    BigInt neg_a = a;
    neg_a.negate();
    return this->add(neg_a);
}

void BigInt::print_result() const {
    std::cout << "Bits: ";
    for (int i = digits.size() - 1; i >= 0; --i) {
        uint32_t word = static_cast<uint32_t>(digits[i]);
        for (int j = 31; j >= 0; --j) {
            std::cout << ((word >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}



std::ostream & operator<<(std::ostream &out, const BigInt &x) {
    if (x.digits.empty()) {
        out << "0x0";
        return out;
    }

    bool negative = (x.digits.back() < 0);
    BigInt temp = x;
    if (negative) {
        temp.negate();
    }

    out << (negative ? "-0x" : "0x");

    out << std::hex;

    bool leadingZero = true; 

    for (int i = temp.digits.size() - 1; i >= 0; --i) {
        uint32_t digitValue = static_cast<uint32_t>(temp.digits[i]);

        if (leadingZero) {
            if (digitValue != 0) {
                leadingZero = false; 
                out << digitValue;
            }
        } else {
            out << std::setw(8) << std::setfill('0') << digitValue; 
        }
    }

    if (leadingZero) {
        out << "0"; 
    }

    out << std::dec << std::setfill(' ');

    return out;
}

int main() {
    BigInt a = INT32_MAX;
    BigInt b = INT32_MIN;
    BigInt e = a.add(b);
    e.print_result();
    std::cout << e << std::endl;
    return 0;
}
