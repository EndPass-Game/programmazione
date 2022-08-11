#pragma once
#include "datastruct/vector.hpp"

namespace datastruct {
    template <class T>
    class Stack {
      private:
        Vector<T> data_;

      public:
        Stack()
            : data_(0) {}

        bool isEmpty() const {
            return data_.isEmpty();
        }

        T top() const {
            return data_.back();
        }

        void push(T element) {
            data_.push_back(element);
        }

        T last() {
            int last = data_.size() - 1;
            return data_[last];
        }

        T pop() {
            return data_.pop_back();
        }
    };
}  // namespace datastruct