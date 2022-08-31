#pragma once
#include "datastruct/vector.tpp"

namespace datastruct {
    template <class T>
    class Stack : private Vector<T>{
      public:
        Stack();

        bool isEmpty() const;

        T top() const;

        void push(T element);

        T last();

        T pop();
    };

    template <class T>
    Stack<T>::Stack()
        : Vector<T>(0) {}

    template <class T>
    bool Stack<T>::isEmpty() const {
        return Vector<T>::isEmpty();
    }

    template <class T>
    T Stack<T>::top() const {
        return Vector<T>::back();
    }

    template <class T>
    void Stack<T>::push(T element) {
        Vector<T>::push_back(element);
    }

    template <class T>
    T Stack<T>::last() {
        return Vector<T>::at(Vector<T>::size() - 1);
    }

    template <class T>
    T Stack<T>::pop() {
        return Vector<T>::pop_back();
    }
}  // namespace datastruct