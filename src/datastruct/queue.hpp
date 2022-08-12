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

        size_t _getHigherPowerOfTwo(size_t n) {
            size_t x = 1;
            while (x <= size_) {
                x <<= 1;
            }
            return x;
        }

        void _resize(size_t size) {
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

      public:
        Queue(size_t size) {
            end_ = 0;
            start_ = 0;
            size_ = 0;
            realSize_ = _getHigherPowerOfTwo(size);
            data_ = new T[realSize_];
        }
        Queue()
            : Queue(0) {}
        ~Queue() {
            delete[] data_;
        }

        size_t size() const {
            return size_;
        }

        size_t isEmpty() const {
            return size_ == 0;
        }

        void push(T element) {
            if (size_ == realSize_) {
                _resize(size_);
            }
            data_[end_] = element;
            end_ += 1;
            size_ += 1;
            if (end_ == realSize_) end_ -= realSize_;
        }

        T &last() {
            return data_[end_ - 1];
        }

        T &first() {
            return data_[start_];
        }

        T pop() {
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

        T &operator[](const int index) const {
            return data_[(start_ + index) % realSize_];
        }
        T &at(const int index) const {
            return data_[(start_ + index) % realSize_];
        }
    };
}  // namespace datastruct