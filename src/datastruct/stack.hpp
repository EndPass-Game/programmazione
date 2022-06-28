#pragma once
#include "datastruct/vector.hpp"

namespace datastruct {
template<class T>
class Stack {
  private:
    Vector<T> data_;
  public:
    Stack(): Stack(0) {}

    bool isEmpty() const {
        return data_.isEmpty();
    }

    T top() const {
        return data_.back();
    }

    void push(T element) {
        data_.push_back(element);
    }

    T pop() {
        return data_.pop_back();
    }
};
} // namespace datastruct