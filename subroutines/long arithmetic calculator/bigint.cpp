#include "bigint.hpp"
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <stack>


BigInt::BigInt() {
    digits.push_back(0);
}


BigInt::BigInt(int value) {
    int32_t word = static_cast<int32_t>(value & 0xFFFFFFFF);
    digits.push_back(word);
    if (word == INT32_MIN) {
        digits.push_back(-1);
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
        uint64_t sum = (static_cast<uint32_t>(digits[i]) & 0xFFFFFFFF) + carry;
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
BigInt::operator*(const BigInt& y) const {
    BigInt x = *this;
    BigInt zero = 0;
    if (x == zero || y == zero) {
        return BigInt(0);
    }
    size_t len = std::max(x.digits.size(), y.digits.size());
    size_t result_size = 2 * len;
    
    bool x_negative = !x.digits.empty() && x.digits.back() < 0;
    bool y_negative = !y.digits.empty() && y.digits.back() < 0;
    
    BigInt y_copy = y;
    if (x_negative) x.negate();
    if (y_negative) y_copy.negate();

    size_t power = 1;
    while (power < len) power *= 2;
    x.digits.resize(power, 0);
    y_copy.digits.resize(power, 0);
    len = power;

    BigInt result;
    result.digits.resize(result_size, 0);

    for (size_t i = 0; i < len; ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j < len; ++j) {
            uint64_t current = static_cast<uint64_t>(static_cast<uint32_t>(x.digits[i])) *
                            static_cast<uint64_t>(static_cast<uint32_t>(y_copy.digits[j])) +
                            static_cast<uint64_t>(static_cast<uint32_t>(result.digits[i + j])) +
                            carry;
            
            result.digits[i + j] = static_cast<int32_t>(current & 0xFFFFFFFF);
            carry = current >> 32;
        }
        if (carry > 0 && i + len < result.digits.size()) {
            result.digits[i + len] += static_cast<int32_t>(carry);
        }
    }
       
    
    for (size_t i = 0; i < result.digits.size() - 1; ++i) {
        uint64_t current = static_cast<uint64_t>(static_cast<uint32_t>(result.digits[i]));
        result.digits[i] = static_cast<int32_t>(current & 0xFFFFFFFF);
        result.digits[i + 1] += static_cast<int32_t>(current >> 32);
    }

    if ((x_negative) || (y_negative) && result.digits.size() > 1) {
        while (result.digits.size() > 1 && 
               ((result.digits.back() == 0 && (result.digits[result.digits.size() - 2] & 0x80000000) == 0) ||
                (result.digits.back() == -1 && (result.digits[result.digits.size() - 2] & 0x80000000) != 0x0))) {
            result.digits.pop_back();
        }
    }
    if (x_negative != y_negative) {
        result.negate();
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


std::ostream & 
operator<<(std::ostream &out, const BigInt &x) {
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
    BigInt a("ffffffffffffffffffffffffffffffff");
    BigInt b("-fffffffffffefefefffffffffffefef");
    std::cout << a * b << std::endl;
    return 0;
}