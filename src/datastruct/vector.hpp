#pragma once
#include <stddef.h> // size_t

namespace datastruct {

// implementazione di vector che utilizza un array dinamico doubling-halving
template<class T>
class Vector {
  private:
    size_t size_; // size of used memory
    size_t realSize_; // size of allocated memory
    T *data_;

    // per l'utilizzo della doubling-halving ho bisogno della prima potenza di 2 maggiore di un numero
    // questa funzione restituisce ciò.
    size_t _getHigherPowerOfTwo(size_t n) {
        size_t x = 1;
        while (x <= n) {
            x <<= 1;
        }
        return x;
    }

    // versione del resize privata. Più veloce rispetto alla pubblica
    // in quanto non deve ricavare la nuova size.
    void _resize(size_t size, size_t newRealSize) {
        int endCopyIdx = size < size_ ? size : size_; // minore fra i due
        size_ = size; 
        T *new_space = new T[newRealSize];
        for (int i = 0; i < endCopyIdx; i++) {
            new_space[i] = data_[i];
        }
        delete []data_;
        data_ = new_space;
        realSize_ = newRealSize;
    }

    void _copyFrom(const Vector<T> &other) {
        size_ = other.size_;
        realSize_ = other.realSize_;
        data_ = new T[realSize_];
        for (unsigned int i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
  public:
    Vector(size_t size) {
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);    
        data_ = new T[realSize_];
    }

    Vector(): Vector(0) {}

    Vector(const Vector<T> &other) {
        this->_copyFrom(other);
    }

    ~Vector() {
        delete []data_;
    }

    size_t size() const {
        return size_;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    T &operator [](const int index) const {
        return data_[index];
    }

    T &at(const int index) const {
        return data_[index];
    }

    // se il vettore è vuoto ritorna l'elemento del costruttore di default del tipo dato,
    // altrimenti ritorna l'ultimo elemento
    T back() const {
        if (isEmpty()) return T();
        return data_[size_ - 1];
    }

    // push con doubling-halving
    void push_back(T element) {
        if (size_ == realSize_) {
            _resize(size_, realSize_ * 2);
        }

        data_[size_] = element;
        size_ += 1;
    }

    // se il vettore è vuoto ritorna l'elemento del costruttore di default del tipo dato,
    // altrimenti ritorna l'elemento rimosso.
    T pop_back() {
        if (isEmpty()) return T();
        if (size_ == realSize_ / 4) {
            _resize(size_, realSize_ / 2);
        }
        size_ -= 1;
        return data_[size_];
    }

    // rimuove l'elemento da index senza preservare l'ordine dei restanti elementi
    // se l'index è invalido ritorna l'elemento del costruttore di default
    T remove(size_t index) {
        if (index >= size_ or index < 0) return T();
        if (size_ == realSize_ / 4) {
            _resize(size_, realSize_ / 2);
        }
        T element = data_[index];
        size_ -= 1;
        data_[index] = data_[size_];
        return element;
    }

    // ridimensiona l'array. Se lo spazio più piccolo, gli elementi con index maggiore sono troncati
    // tutti il resto degli elementi sono ricopiati
    void resize(size_t size) {
        size_t newRealSize = _getHigherPowerOfTwo(size);
        _resize(size, newRealSize);
    }

    // ridimensiona l'array per poter contenere SIZE elementi e assegna 
    // il valore VAL in input per indici 0..SIZE-1.
    void assign(size_t size, T val) {
        resize(size);
        for (unsigned int i = 0; i < size; i++) {

            data_[i] = val;
        }
        size_ = size;
    }

    void clear() {
        delete []data_;
        realSize_ = 1; // 1 per evitare errori nel *2 in push_back
        size_ = 0;
        data_ = new T[realSize_];
    }
    bool operator==(const Vector<T> &other) = delete;

    Vector<T> &operator=(const Vector<T> &other) {
        if (this == &other) return *this;

        delete []data_;
        this->_copyFrom(other);

        return *this;
    }
};
}; // namespace datastruct