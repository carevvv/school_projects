#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <mutex>

class Singleton {
public:
    static Singleton& getInstance();

    void showMessage() const;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

private:
    Singleton();
    ~Singleton();
};

#endif
