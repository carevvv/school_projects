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
        if (this->num_shared && --(*this->num_shared) == 0) {
            delete this->data;
            delete this->num_shared;
            if (this->num_weak && *this->num_weak == 0) {
                delete this->num_weak;
            }
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
        if (this->num_weak) {
            --(*this->num_weak);
            iif (*this->num_shared == 0 && *this->num_weak == 0) {
                delete this->num_shared;
                delete this->num_weak;
                num_shared = nullptr;
                num_weak = nullptr;
                data = nullptr;
            }
        }
        this->data = nullptr;
        this->num_shared = nullptr;
        this->num_weak = nullptr;
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


void test_unique_ptr() {
    // Test 1: Creating a unique_ptr that owns a dynamically allocated integer
    pointers::unique_ptr<int> ptr1(new int(10));  // unique_ptr that points to an integer with value 10
    assert(*ptr1 == 10);  // Assert that ptr1 points to value 10
    std::cout << "Test 1: ptr1 owns the integer: " << *ptr1 << std::endl;  // Should print 10

    // Test 2: Move constructor - transferring ownership
    pointers::unique_ptr<int> ptr2(std::move(ptr1));  // Ownership of the integer is moved to ptr2
    assert(ptr1.operator->() == nullptr);  // Assert that ptr1 is now empty
    assert(*ptr2 == 10);  // Assert that ptr2 now points to value 10
    std::cout << "Test 2: After move, ptr2 owns the integer: " << *ptr2 << std::endl;  // Should print 10
    // ptr1 should now be empty (nullptr), dereferencing it will be an error (we won't dereference ptr1)

    // Test 3: Move assignment - moving ownership from one unique_ptr to another
    pointers::unique_ptr<int> ptr3(new int(20));  // Create a new unique_ptr that owns an integer with value 20
    assert(*ptr3 == 20);  // Assert that ptr3 points to value 20
    std::cout << "Test 3: ptr3 owns the integer: " << *ptr3 << std::endl;  // Should print 20
    ptr3 = std::move(ptr2);  // Ownership of the integer in ptr2 is moved to ptr3
    std::cout << "moved" << std::endl;
    assert(ptr2.operator->() == nullptr);  // Assert that ptr2 is now empty
    assert(*ptr3 == 10);  // Assert that ptr3 now points to value 10 after move assignment
    std::cout << "Test 3: After move assignment, ptr3 owns the integer: " << *ptr3 << std::endl;  // Should print 10
    // ptr2 is now empty (nullptr)

    // Test 4: Test with custom class
    class MyClass {
    public:
        MyClass(int a, int b) : x(a), y(b) {}
        int x, y;
    };

    pointers::unique_ptr<MyClass> myPtr(new MyClass(5, 10));
    assert(myPtr->x == 5);  // Assert that myPtr->x is 5
    assert(myPtr->y == 10); // Assert that myPtr->y is 10
    std::cout << "Test 4: MyClass object owned by unique_ptr, x = " << myPtr->x << ", y = " << myPtr->y << std::endl;
    // Should print: MyClass object owned by unique_ptr, x = 5, y = 10

    // Test 5: Destruction of unique_ptr, automatically deletes the resource
    // No explicit test needed. When the function scope ends, unique_ptr should automatically delete its owned resource.
    // Assertions are not needed here as destructors are called automatically at the end of the function.
}

void test_shared_ptr_and_weak_ptr() {
    // Test 1: Creating shared_ptr and reference counting
    pointers::shared_ptr<int> sp1(new int(20));  // shared_ptr that owns an integer with value 20
    assert(*sp1 == 20);  // Assert that sp1 points to value 20
    std::cout << "Test 1: sp1 owns the integer: " << *sp1 << std::endl;  // Should print 20

    // Test 2: Creating another shared_ptr that shares ownership
    pointers::shared_ptr<int> sp2(sp1);  // sp2 shares ownership of the same integer
    assert(*sp2 == 20);  // Assert that sp2 also points to value 20
    assert(*sp1 == 20);  // Assert that sp1 still points to value 20
    std::cout << "Test 2: sp2 shares ownership with sp1, value: " << *sp2 << std::endl;  // Should print 20

    // Test 3: Checking reference count via weak_ptr
    pointers::weak_ptr<int> wp1(sp1);  // weak_ptr pointing to the shared_ptr
    assert(!wp1.expired());  // Assert that wp1 is not expired because sp1 is still valid
    std::cout << "Test 3: weak_ptr is not expired, value: " << *wp1 << std::endl;  // Should print 20
    

    // Test 4: Expired weak_ptr after shared_ptr goes out of scope
    {
        pointers::shared_ptr<int> sp3(new int(30));  // New shared_ptr with value 30
        std::cout << "maked sp3 " << *sp3 << std::endl;
        pointers::weak_ptr<int> wp2(sp3);  // weak_ptr pointing to sp3
        std::cout << "maked wp2 " << *wp2 << std::endl;
        assert(!wp2.expired());  // Assert that wp2 is not expired
        std::cout << "asserted " << *sp3 << std::endl;
    }  // sp3 and wp2 are destroyed here, in the correct order
    std::cout << "Test 4: weak_ptr expired after shared_ptr goes out of scope." << std::endl;

    // Test 5: Creating weak_ptr from a shared_ptr and accessing the value
    pointers::shared_ptr<int> sp4(new int(40));
    pointers::weak_ptr<int> wp3(sp4);  // weak_ptr pointing to sp4
    assert(!wp3.expired());  // Assert that wp3 is not expired
    assert(*wp3 == 40);  // Assert that wp3 points to value 40 through sp4
    std::cout << "Test 5: weak_ptr points to value: " << *wp3 << std::endl;  // Should print 40

    // Test 6: weak_ptr expired with no shared_ptr ownership
    pointers::shared_ptr<int> sp5;  // Default shared_ptr (nullptr)
    pointers::weak_ptr<int> wp4(sp5);  // weak_ptr pointing to nullptr shared_ptr
    assert(wp4.expired());  // Assert that wp4 is expired, as it points to nothing
    std::cout << "Test 6: weak_ptr expired with no shared_ptr ownership." << std::endl;
}


int main() {
    test_shared_ptr_and_weak_ptr();
    test_unique_ptr();
    return 0;
}
