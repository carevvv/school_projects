#include "complexint.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>


Complex::Complex(double a, double b) {
    this->re = a;
    this->im = b;
}


Complex::Complex(const Complex &x) {
    this->re = x.re;
    this->im = x.im;
}


Complex::Complex(const std::string& value) {
    bool re_negative = false;
    bool im_negative = false;
    std::string result = value;

    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    if (result.size() == 0) {
        this->re = 0;
        this->im = 0;
        return;
    }

    if (result[0] == '-') {
        re_negative = true;
        result = result.substr(1);
    } else if (result[0] == '+') {
        result = result.substr(1);
    }

    if (result.find('e') == std::string::npos && result.find('E') == std::string::npos) {
        size_t im_neg = result.find('-');
        size_t im_pos = result.find('+');
        size_t start;
        if (im_neg != std::string::npos) {
            im_negative = true;
            start = im_neg + 1;
        } else if (im_pos != std::string::npos) {
            im_negative = false;
            start = im_pos + 1;
        } else {
            size_t i = result.find('i');
            if (i == std::string::npos) {
                this->re = std::stold(result) * (re_negative ? -1 : 1);
                this->im = 0;
                return;
            }
            else {
                if (result.size() == 1) {
                    this->re = 0;
                    this->im = 1 * (re_negative ? -1 : 1);
                    return;
                }
                this->im = std::stold(result.substr(0, i)) * (re_negative ? -1 : 1);
                this->re = 0;
                return;
            }
        }

        size_t end = result.find('i');
        if (end == std::string::npos) {
            std::cerr << "Error: Invalid complex number format. Example: \"-12 + 2i\"" << std::endl;
            exit(1);
        }
        this->re = std::stold(result.substr(0, start)) * (re_negative ? -1 : 1);
        
        if (result.substr(start, end - start).size() == 0) {
            this->im = 1 * (im_negative ? -1 : 1);
        } else {
            this->im = std::stold(result.substr(start, end - start)) * (im_negative ? -1 : 1);
        }
    } else {
        size_t i_pos = result.find('i');

        if (i_pos == std::string::npos) {
            std::string real_part = result;

            if (!real_part.empty() && (real_part.back() == 'f' || real_part.back() == 'F')) {
                real_part = real_part.substr(0, real_part.size() - 1);
            }

            try {
                this->re = std::stold(real_part) * (re_negative ? -1 : 1);
                this->im = 0;
                return;
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid complex number format (real part). " << e.what() << std::endl;
                exit(1);
            }
        } else {
            std::string pre_i = result.substr(0, i_pos);
            std::string post_i = result.substr(i_pos + 1);
            if (!post_i.empty()) {
                std::cerr << "Error: Invalid complex number format. Unexpected characters after 'i'." << std::endl;
                exit(1);
            }

            std::string real_part, imag_part;
            size_t split_pos = std::string::npos;
            bool im_sign_found = false; 


            for (size_t pos = pre_i.length(); pos > 0; --pos) {
                if ((pre_i[pos - 1] == '+' || pre_i[pos - 1] == '-') &&
                    (pos == 1 || (pre_i[pos - 2] != 'e' && pre_i[pos - 2] != 'E'))) {
                    split_pos = pos - 1;
                    im_sign_found = true;
                    im_negative = (pre_i[pos - 1] == '-') ? true : false;
                    break;
                }
            }

            if (split_pos != std::string::npos) {
                real_part = pre_i.substr(0, split_pos);
                imag_part = pre_i.substr(split_pos);
            } else {
                im_negative = re_negative;
                real_part = "0";
                imag_part = pre_i;
            }

            if (!imag_part.empty() && (imag_part[0] == '+' || imag_part[0] == '-')) {
                imag_part = imag_part.substr(1);
            }

            if (!real_part.empty() && (real_part.back() == 'f' || real_part.back() == 'F')) {
                real_part = real_part.substr(0, real_part.size() - 1);
            }
            if (!imag_part.empty() && (imag_part.back() == 'f' || imag_part.back() == 'F')) {
                imag_part = imag_part.substr(0, imag_part.size() - 1);
            }

            if (imag_part.empty()) {
                imag_part = "1";
            }

            try {
                real_part.erase(std::remove(real_part.begin(), real_part.end(), ' '), real_part.end());
                if (real_part.empty() || real_part == "0") {
                    this->re = 0;
                } else {
                    this->re = std::stold(real_part) * (re_negative ? -1 : 1);
                }

                this->im = std::stold(imag_part) * (im_negative ? -1 : 1);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid complex number format. " << e.what() << std::endl;
                exit(1);
            }
        }
    }
}


Complex
Complex::operator+(const Complex &x) const {
    return Complex(this->re + x.re, this->im + x.im);
}


Complex
Complex::operator+(const int x) const {
    return Complex(this->re + x, this->im);
}


Complex
Complex::operator-(const Complex &x) const {
    return Complex(this->re - x.re, this->im - x.im);
}

Complex 
Complex::operator-(const int x) const {
    return Complex(this->re - x, this->im);
}


Complex 
Complex::operator*(const Complex &x) const {
    return Complex(this->re * x.re - this->im * x.im, this->re * x.im + this->im * x.re);
}


Complex 
Complex::operator*(const int x) const {
    return Complex(this->re * x, this->im * x);
}


Complex 
Complex::operator/(const Complex &x) const {
    if (pow(x.re, 2) + pow(x.im, 2) == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        exit(1);
    }
    return Complex((this->re * x.re + this->im * x.im) / (pow(x.re, 2) + pow(x.im, 2)), (this->im * x.re - this->re * x.im) / (pow(x.re, 2) + pow(x.im, 2)));
}


Complex
Complex::operator/(const int x) const {
    if (x == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        exit(1);
    }
    return Complex(this->re / x, this->im / x);
}


Complex 
Complex::operator+() const {
    return *this;
}


Complex 
Complex::operator-() const {
    return Complex(-re, -im);
}


Complex 
Complex::operator^(const int x) const {
        double magnitude = sqrt(this->re * this->re + this->im * this->im); 
        double angle = atan2(im, re);             
        double magnitude_n = pow(magnitude, x);  
        double angle_n = angle * x;

        double real_part = magnitude_n * cos(angle_n); 
        double imag_part = magnitude_n * sin(angle_n);

        return Complex(real_part, imag_part);
}


bool 
Complex::operator==(const Complex &x) const {
    return this->re == x.re && this->im == x.im;
}


bool
Complex::operator!=(const Complex &x) const {
    return !(*this == x);
}   


bool 
Complex::operator>(const Complex &x) const {    
    return (re * re + im * im) > (x.re * x.re + x.im * x.im);
}


bool
Complex::operator<(const Complex &x) const {
    return (re * re + im * im) < (x.re * x.re + x.im * x.im);
}


bool
Complex::operator>=(const Complex &x) const {
    return (re * re + im * im) >= (x.re * x.re + x.im * x.im);
}


bool 
Complex::operator<=(const Complex &x) const {
    return (re * re + im * im) <= (x.re * x.re + x.im * x.im);
}


std::ostream & operator<<(std::ostream &out, const Complex &x) {
    if (x.im < 0) {
        if (x.im == -1) {
            out << x.re << " - i";
        } else {
            out << x.re << " - " << -x.im << "i";
        }
        return out;
    }
    if (x.im == 1) {
        std::cout << x.re << " + i";
        return out;
    } else {
        out << x.re << " + " << x.im << "i";
    }
    return out;
}


int
main (void) {
    Complex a("2 + i");
    Complex b("3 - i");
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    Complex c = a + b;
    Complex d = a - b;
    Complex e = a * b;
    Complex f = a / b;
    Complex g = a ^ 2;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;

    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a < b) << std::endl;
    std::cout << (a >= b) << std::endl;
    std::cout << (a <= b) << std::endl;
    return 0;
}