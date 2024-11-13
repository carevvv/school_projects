#include "singleton.hpp"
#include <iostream>
#include <stdexcept>


template <typename T>
T& Singleton<T>::getInstance() {
    static T instance;
    std::cout << "Singleton instance returned." << std::endl;
    return instance;
}

template <typename T>
Singleton<T>::Singleton() {
    std::cout << "Singleton instance created." << std::endl;
}

template <typename T>
Singleton<T>::~Singleton() {
    std::cout << "Singleton instance destroyed." << std::endl;
}


int 
main(void) {
    try {
        Singleton<int>::getInstance(); 
    }
    catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
