#include <iostream>
#include "pointers.hpp"
#include <stdexcept>
#include <vector>
#include <cassert>
   


namespace pointers {
    template <typename T>
    unique_ptr<T>::unique_ptr(T &&x) {
        this->data = new T(std::move(x));        
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(T *x) {
        this->data = x;
    }

    template <typename T>
    unique_ptr<T>::unique_ptr() {
        this->data = nullptr;
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) {
        this->data = other.data;
        other.data = nullptr;
    }

    template <typename T>
    unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) {
        if (this != &other) {
            delete this->data;
            this->data = other.data;
            other.data = nullptr;
            delete other.data;
        }
        return *this;
    }

    template <typename T>
    T &unique_ptr<T>::operator*() const {
        return *this->data;
    }
    
    template <typename T>
    T *unique_ptr<T>::operator->() const {
        return this->data;
    }

    template <typename T>
    unique_ptr<T>::~unique_ptr () {
        delete this->data;        
    }


    template <typename T>
    shared_ptr<T>::shared_ptr(T&& x) {
        this->data = new T(std::move(x));
        this->num_shared = new size_t(1);
        this->num_weak = new size_t(0);
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(T* x) {
        this->data = x;
        if (x) {
            this->num_shared = new size_t(1);
            this->num_weak = new size_t(0);
        } else {
            this->num_shared = nullptr;
            this->num_weak = nullptr;
        }
    }

    template <typename T>
    shared_ptr<T>::shared_ptr() {
        this->data = nullptr;
        this->num_shared = nullptr;
        this->num_weak = nullptr;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T>& other) {
        this->data = other.data;
        this->num_shared = other.num_shared;
        this->num_weak = other.num_weak;
        if (this->num_shared) {
            ++(*this->num_shared);
        }
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) {
        if (this != &other) {
            if (this->num_shared && --(*this->num_shared) == 0) {
                delete this->data;
                delete this->num_shared;
                if (this->num_weak && *this->num_weak == 0) {
                    delete this->num_weak;
                }
            }
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;
            if (this->num_shared) {
                ++(*this->num_shared);
            }
        }
        return *this;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& other) {
        this->data = other.data;
        this->num_shared = other.num_shared;
        this->num_weak = other.num_weak;

        other.data = nullptr;
        other.num_shared = nullptr;
        other.num_weak = nullptr;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other) {
        if (this != &other) {
            if (this->num_shared && --(*this->num_shared) == 0) {
                delete this->data;
                delete this->num_shared;
                if (this->num_weak && *this->num_weak == 0) {
                    delete this->num_weak;
                }
            }
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;

            other.data = nullptr;
            other.num_shared = nullptr;
            other.num_weak = nullptr;
        }
        return *this;
    }

    template <typename T>
    T* shared_ptr<T>::operator->() const {
        return this->data;
    }

    template <typename T>
    T& shared_ptr<T>::operator*() const {
        return *this->data;
    }

    template <typename T>
    shared_ptr<T>::~shared_ptr() {
          if (num_shared && --(*num_shared) == 0) {
              delete data;
              delete num_shared;
              delete num_weak;
          } else if (!data) {
              delete num_shared;
              delete num_weak;
          }
      }

    
    template <typename T>
    weak_ptr<T>::weak_ptr(const weak_ptr<T>& other) {
        this->data = other.data;
        this->num_shared = other.num_shared;
        this->num_weak = other.num_weak;
        if (this->num_weak) {
            ++(*this->num_weak);
        }
    }

    template <typename T>
    weak_ptr<T>&weak_ptr<T>::operator=(const weak_ptr<T>& other) {
        if (this != &other) {
            this->release();
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;
            if (this->num_weak) {
                ++(*this->num_weak);
            }
        }
        return *this;
    }

    template <typename T>
    weak_ptr<T>::weak_ptr(const shared_ptr<T>& other) {
        if (other.data) {
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;
            if (this->num_weak) {
                ++(*this->num_weak);
            }
        } else {
            this->data = nullptr;
            this->num_shared = nullptr;
            this->num_weak = nullptr;
        }
    }

    template <typename T>
    weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& other) {
        this->release();
        if (this->data != other.data) {
            release();
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;
            if (this->num_weak) {
                ++(*this->num_weak);
            }
        } else {
            this->data = nullptr;
            this->num_shared = nullptr;
            this->num_weak = nullptr;
        }
        return *this;
    }

    template <typename T>
    weak_ptr<T>::weak_ptr(weak_ptr<T>&& other) {
        this->data = other.data;
        this->num_shared = other.num_shared;
        this->num_weak = other.num_weak;

        other.data = nullptr;
        other.num_shared = nullptr;
        other.num_weak = nullptr;
    }

    template <typename T>
    weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& other) {
        if (this != &other) {
            this->release();
            this->data = other.data;
            this->num_shared = other.num_shared;
            this->num_weak = other.num_weak;
            other.data = nullptr;
            other.num_shared = nullptr;
            other.num_weak = nullptr;
        }
        return *this;
    }

    template <typename T>
    weak_ptr<T>::~weak_ptr() {
        this->release();
    }

    template <typename T>
    void weak_ptr<T>::release() {
          if (num_weak && --(*num_weak) == 0 && *num_shared == 0) {
              delete num_weak;
          }
      }
    template <typename T>
    bool weak_ptr<T>::expired() const {
        return !this->num_shared || *this->num_shared == 0;
    }
    
    template <typename T>
    T& weak_ptr<T>::operator*() const {
        if (this->expired()) {
            throw std::runtime_error("weak_ptr: попытка разыменовать просроченный указатель");
        }
        return *this->data;
    }

    template <typename T>
    T* weak_ptr<T>::operator->() const {
        if (this->expired()) {
            throw std::runtime_error("weak_ptr: попытка обратиться к члену через просроченный указатель");
        }
        return this->data;
    }
};
