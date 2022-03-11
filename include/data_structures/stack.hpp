#include "vector.hpp"

template<class T>
class Stack {
  private:
    Vector<T> data_;
  public:
    Stack(uint size) {
        data_ = Vector<T>(size);
    }

    Stack(): Stack(0) {}

    uint isEmpty() const {
        return data_.isEmpty();
    }

    void push(T element) {
        data_.push_back(element);
    }

    T pop_back() {
        return data_.pop_back();
    }
};