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


BigInt::BigInt(const std::string &value) {
    bool is_negative = false;
    std::string hex_value = value;
    if (value[0] == '-') {
        is_negative = true;
        hex_value = value.substr(1); 
    }

    digits.clear();

    size_t length = hex_value.length();
    size_t num_blocks = (length + 7) / 8; 

    for (size_t i = 0; i < num_blocks; ++i) {
        size_t start = (length > (i + 1) * 8) ? length - (i + 1) * 8 : 0;
        size_t len = (length > (i + 1) * 8) ? 8 : length - i * 8;
        
        std::string block = hex_value.substr(start, len);
        uint32_t digit = static_cast<uint32_t>(std::stoul(block, nullptr, 16)); 

        digits.push_back(digit);
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] & 0x80000000) { 
            if (i == digits.size() - 1) {
                digits.push_back(0); 
            }
        }
    }

    if (is_negative) {
        this->negate();
    }
}


void 
BigInt::negate() {
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


void 
BigInt::print_result() const {
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


BigInt 
BigInt::operator+(const BigInt &a) const {
    BigInt result;
    size_t maxSize = std::max(this->digits.size(), a.digits.size());
    result.digits.resize(maxSize, 0);

    int64_t carry = 0;
    bool thisneg = (this->digits.back() & 0x80000000);
    bool aneg = (a.digits.back() & 0x80000000); 

    for (size_t i = 0; i < maxSize; ++i) {
        int64_t class_digit = (i < this->digits.size()) ? static_cast<uint32_t>(this->digits[i]) : (thisneg ? 0xFFFFFFFF : 0);
        int64_t a_digit = (i < a.digits.size()) ? static_cast<uint32_t>(a.digits[i]) : (aneg ? 0xFFFFFFFF : 0);

        int64_t sum = class_digit + a_digit + carry;

        result.digits[i] = static_cast<int32_t>(sum & 0xFFFFFFFF);

        carry = sum >> 32;
    }

    bool result_neg = (result.digits.back() & 0x80000000);

    if ((thisneg == aneg) && (result_neg != thisneg)) {
        if (thisneg == 0 && result_neg == 1) {
            result.digits.push_back(0);
        } else {
            result.digits.push_back(result_neg ? -1 : 0);
        }
    } else if ((result_neg == thisneg) && result.digits.size() > 1) {
        while (result.digits.size() > 1 && 
               ((result.digits.back() == 0 && (result.digits[result.digits.size() - 2] & 0x80000000) == 0) ||
                (result.digits.back() == -1 && (result.digits[result.digits.size() - 2] & 0x80000000) != 0x0))) {
            result.digits.pop_back();
        }
    }

    return result;
}


BigInt 
BigInt::operator-(const BigInt &a) const {
    BigInt neg_a = a;
    neg_a.negate();
    return this->operator+(neg_a);
}


BigInt
BigInt::operator*(const BigInt &x) const {
    BigInt result;
    for (size_t i = 0; i < x.digits.size(); ++i) {
        result = result + (*this * x.digits[i]);
    }
    return result;
}

BigInt
BigInt::operator+() const {
    return *this;
}


BigInt
BigInt::operator-() const {
    BigInt result = *this;
    result.negate();
    return result;
}


bool 
BigInt::operator==(const BigInt &x) const {
    if (this->digits.size() != x.digits.size()) {
        return false;
    }
    for (size_t i = 0; i < this->digits.size(); ++i) {
        if (this->digits[i] != x.digits[i]) {
            return false;
        }
    }
    return true;
}


bool
BigInt::operator!=(const BigInt &x) const {
    return !(*this == x);
}


bool 
BigInt::operator>(const BigInt &x) const {
    if (this->digits[this->digits.size() - 1] == 0 && x.digits[x.digits.size() - 1] == -1) {
        return true;
    } else if (this->digits[this->digits.size() - 1] == -1 && x.digits[x.digits.size() - 1] == 0) {
        return false;
    }
    if (this->digits.size() > x.digits.size() && (this->digits[this->digits.size() - 1] == 0 && x.digits[x.digits.size() - 1] == 0)) {
        return true;
    } else if (this->digits.size() < x.digits.size() && (this->digits[this->digits.size() - 1] == 0 && x.digits[x.digits.size() - 1] == 0)){
        return false;
    } 
    if (this->digits.size() < x.digits.size() && (this->digits[this->digits.size() - 1] == -1 && x.digits[x.digits.size() - 1] == -1)) {
        return true;
    } else if (this->digits.size() > x.digits.size() && (this->digits[this->digits.size() - 1] == -1 && x.digits[x.digits.size() - 1] == -1)){
        return false;
    } 

    for (int i = this->digits.size() - 1; i >= 0; --i) {
        if (this->digits[i] < x.digits[i]) {
            return false;
        } else if (this->digits[i] > x.digits[i]) {
            return true;
        }
    }
    return false;
}


bool 
BigInt::operator<(const BigInt &x) const {
    if (*this == x) {
        return false;
    }
    return !(*this > x);
}   


bool 
BigInt::operator>=(const BigInt &x) const {
    bool e = (*this > x);
    bool f = (*this == x);
    return e || f;
}


bool 
BigInt::operator<=(const BigInt &x) const {
    bool e = (*this < x);
    bool f = (*this == x);
    return e || f;
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
    out << (negative ? "-" : "");
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



int 
main(void) {
    BigInt a("1");
    BigInt b("2");
    a.print_result();
    b.print_result();
    BigInt c = (a + b > a - b);
    std::cout << c << std::endl;
    return 0;
}
