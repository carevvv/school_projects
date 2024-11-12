#include <iostream>
#include "pointers.hpp"

#include <vector>


namespace pointers {
    template <typename T>
    unique_ptr<T>::unique_ptr(T &&x) {
        data = new T(std::move(x));        
    }


    template <typename T>
    T *unique_ptr<T>::operator->() {
        return this->data;
    } 

    template <typename T>
    unique_ptr<T>::~unique_ptr () {
        delete this->data;        
    }

    
};


int main() {
    pointers::unique_ptr<std::vector<int>> ptr = std::vector<int>(0);
}
