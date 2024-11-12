#include <cstdlib>

#ifndef SMART_PTR_H
#define SMART_PTR_H

namespace pointers {
    template <typename T>
    class unique_ptr {
    public:
        unique_ptr<T>(T &&x);
        unique_ptr<T>(T *x);
        unique_ptr<T>();
        unique_ptr<T>(const unique_ptr<T>&) = delete;
        unique_ptr<T> &operator=(const unique_ptr<T>&) = delete;

        unique_ptr<T>(unique_ptr<T>&&);
        unique_ptr<T> &operator=(unique_ptr<T>&&);

        ~unique_ptr<T>();

        T &operator*() const;
        T *operator->() const;
    private:
        T *data;
    };


    template <typename T>
    class shared_ptr {
    public:
        shared_ptr<T>(T &&x);
        shared_ptr<T>(T *x);
        shared_ptr();
        shared_ptr<T>(const shared_ptr<T>&);
        shared_ptr<T> &operator=(const shared_ptr<T>&);

        shared_ptr<T>(shared_ptr<T>&&);
        shared_ptr<T> &operator=(shared_ptr<T>&&);

        ~shared_ptr<T>();

        T &operator*() const;
        T* operator->() const;
    private:
        T *data;
        size_t *num_shared;
        size_t *num_weak;
        template <typename U> friend class weak_ptr;
    };


    template <typename T>
    class weak_ptr {
    public:
        weak_ptr<T>() = delete;
        weak_ptr<T>(const weak_ptr<T>&);
        weak_ptr<T> &operator=(const weak_ptr<T>&);
        weak_ptr<T>(const shared_ptr<T>&);
        weak_ptr<T> &operator=(const shared_ptr<T>&);

        weak_ptr<T>(weak_ptr<T>&&);
        weak_ptr<T> &operator=(weak_ptr<T>&&);

        ~weak_ptr<T>();
        bool expired() const;

        T& operator*() const;
        T* operator->() const;
    private:
        void release();
        T *data;
        size_t *num_shared;
        size_t *num_weak;
    };
};

#endif