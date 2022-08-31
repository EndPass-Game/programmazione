#pragma once
#include "datastruct/vector.tpp"

namespace datastruct {
    /**
     * @brief Implementazione di una stack, si basa interamente sul vector
     * ma ne riscrive l'interfaccia
     * 
     * @tparam T il tipo di oggetto che la stack deve contenere
     */
    template <class T>
    class Stack : private Vector<T>{
      public:
        /**
         * @brief Costruisce una nuova stack di dimensione size
         */
        Stack();

        /**
         * @returns bool true se la stack è vuota, false altrimenti
         */
        bool isEmpty() const;

        /**
         * @returns T l'elemento in cima alla stack
         * nel caso in cui la stack è vuota vedere il comportamento di pop_back
         * di Vector.
         */
        T top() const;

        /**
         * @brief aggiunge un elemento in cima alla stack
         * 
         * @param element l'elemento da aggiungere
         */
        void push(T element);

        /**
         * @brief rimuove l'elemento in cima alla stack
         * nel caso in cui la stack è vuota vedere il comportamento di pop_back
         * di Vector.
         */
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
    T Stack<T>::pop() {
        return Vector<T>::pop_back();
    }
}  // namespace datastruct