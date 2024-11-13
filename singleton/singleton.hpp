#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <mutex>

template <typename T>
class Singleton {
public:
    static T& getInstance();

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton();
    virtual ~Singleton();
};

#endif 
