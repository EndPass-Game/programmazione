#pragma once
#include <stddef.h>  // size_t
#pragma once
namespace datastruct {
    template <class T>
    class Queue {
      private:
        size_t end_;
        size_t start_;
        size_t size_;
        size_t realSize_;
        T *data_;

        size_t _getHigherPowerOfTwo(size_t n);
        void _resize(size_t size);

      public:
        Queue(size_t size);
        Queue();
        ~Queue();

        size_t size() const;

        size_t isEmpty() const;

        void push(T element);

        T &last();

        T &first();
        T pop();

        T &operator[](const int index) const;

        T &at(const int index) const;
    };

    template <class T>
    size_t Queue<T>::_getHigherPowerOfTwo(size_t n) {
        size_t x = 1;
        while (x <= size_) {
            x <<= 1;
        }
        return x;
    }

    template <class T>
    void Queue<T>::_resize(size_t size) {
        size_t newSize = _getHigherPowerOfTwo(size);
        size_t minSize = size_ < newSize ? size_ : newSize;
        T *new_space = new T[newSize];
        for (size_t i = start_, j = 0; j < minSize; i++, j++) {
            if (i == realSize_) i -= realSize_;
            new_space[j] = data_[i];
        }
        delete[] data_;
        data_ = new_space;
        realSize_ = newSize;
        start_ = 0;
        end_ = size_;
    }

    template <class T>
    Queue<T>::Queue(size_t size) {
        end_ = 0;
        start_ = 0;
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);
        data_ = new T[realSize_];
    }

    template <class T>
    Queue<T>::Queue()
        : Queue(0) {}

    template <class T>
    Queue<T>::~Queue() {
        delete[] data_;
    }

    template <class T>
    size_t Queue<T>::size() const {
        return size_;
    }

    template <class T>
    size_t Queue<T>::isEmpty() const {
        return size_ == 0;
    }

    template <class T>
    void Queue<T>::push(T element) {
        if (size_ == realSize_) {
            _resize(size_);
        }
        data_[end_] = element;
        end_ += 1;
        size_ += 1;
        if (end_ == realSize_) end_ -= realSize_;
    }

    template <class T>
    T &Queue<T>::last() {
        return data_[end_ - 1];
    }

    template <class T>
    T &Queue<T>::first() {
        return data_[start_];
    }

    template <class T>
    T Queue<T>::pop() {
        if (isEmpty()) return T();

        if (size_ == realSize_ / 4) {
            _resize(size_);
        }

        T element = data_[start_];
        start_ += 1;
        size_ -= 1;
        if (start_ == realSize_) start_ -= realSize_;
        return element;
    }

    template <class T>
    T &Queue<T>::operator[](const int index) const { 
        return data_[(start_ + index) % realSize_];
    }

    template <class T>
    T &Queue<T>::at(const int index) const {
        return data_[(start_ + index) % realSize_];
    }
}  // namespace datastruct
