#include <iostream>
#include <memory>
#include "calculator.hpp"

int main() {
    std::cout << "Choose the calculator type:\n";
    std::cout << "1. Long integers\n";
    std::cout << "2. Complex numbers\n";
    std::cout << "Enter 1 or 2: ";

    int choice;
    std::cin >> choice;
    
    std::unique_ptr<BigInt> calculator_bigint;
    std::unique_ptr<Complex> calculator_complex;

    switch (choice) {
        case 1:
            calculator_bigint = std::make_unique<BigInt>();
            break;
        case 2:
            calculator_complex = std::make_unique<Complex>();
            break;
        default:
            std::cerr << "Incorrect choice.\n";
            return 1;
    }

    std::cout << "Enter your expression: ";
    std::cin.ignore(); 
    std::string expression;
    std::getline(std::cin, expression);
    try {
        if (choice == 1) {
            BigInt result = calculator_bigint->calculate(expression);
            std::cout << "Result: " << result << "\n";
        } else {
            Complex result = calculator_complex->calculate(expression);
            std::cout << "Result: " << result << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr <<e.what() << "\n";
    }
    return 0;
}                                                                                                   