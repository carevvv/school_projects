#include <iostream>
#include <string>
#include <bitset>

void print_bits(int n) {
    std::string bits = std::bitset<32>(n).to_string();
    std::cout << bits;
}


int main(void) {
    int n = -5;
    print_bits(n);
    return 0;
}