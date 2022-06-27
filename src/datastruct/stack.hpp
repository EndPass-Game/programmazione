#include "datastruct/vector.hpp"

namespace datastruct {
template<class T>
class Stack {
  private:
    Vector<T> data_;
  public:
    Stack(): Stack(0) {}

    uint isEmpty() const {
        return data_.isEmpty();
    }

    void push(T element) {
        data_.push_back(element);
    }

    T pop() {
        return data_.pop_back();
    }
};
} // namespace datastruct