#include "singleton.hpp"
#include <iostream>
#include <stdexcept>

Singleton& Singleton::getInstance() {
    try {
        static Singleton instance;
        return instance;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception during Singleton initialization: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown exception during Singleton initialization." << std::endl;
        throw;
    }
}

Singleton::Singleton() {
    std::cout << "Singleton instance created." << std::endl;
}

Singleton::~Singleton() {
    std::cout << "Singleton instance destroyed." << std::endl;
}

void
Singleton::showMessage() const {
    std::cout << "Hello from Singleton!" << std::endl;
}



int 
main(void) {
    try {
        Singleton::getInstance().showMessage();
    }
    catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
