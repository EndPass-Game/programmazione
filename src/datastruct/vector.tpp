#pragma once
#include <stddef.h>  // size_t

#include "gamestruct/logger.hpp"
namespace datastruct {
    /**
     * @brief implementazione di vector che utilizza un array dinamico doubling-halving
     * @tparam T il tipo di oggetto che il vettore deve contenere
     */
    template <class T>
    class Vector {
      protected:
        size_t size_;      // size of used memory
        size_t realSize_;  // size of allocated memory
        T *data_;

        /**
         * @brief ritorna la prima potenza di 2 maggiore di un numero
         * per l'utilizzo della doubling-halving ho bisogno della prima potenza di 2 maggiore di un numero
         *
         * @return size_t la prima potenza di 2 maggiore di n
         */
        size_t _getHigherPowerOfTwo(size_t n);

        /**
         * @brief fa il resize dell'array in `data_` alla nuova dimensione `newRealSize`
         * differisce rispetto a `resize(size_t size)` in quanto non deve ricavare la nuova size, ma lo prende in input.
         *
         * @param size la nuova size di `data_`
         * @param newRealSize la size realmente allocata, deve essere calcolata con _getHigherPowerOfTwo(size)
         */
        void _resize(size_t size, size_t newRealSize);

        /**
         * @brief copia tutto il contenuto di un altro vector nel vettore attuale
         *
         * @param other il vettore da copiare
         */
        void _copyFrom(const Vector<T> &other);

      public:
        /**
         * @brief costruisce un nuovo Vector object con dimensione size
         *
         * @param size la dimensione del vettore
         */
        Vector(size_t size);

        /**
         * @brief costruisce un nuvo Vector object con nessun elemento
         */
        Vector();

        /**
         * @brief copy costructor di Vector
         */
        Vector(const Vector<T> &other);

        /**
         * @brief distruttore di Vector, libera la memoria allocata
         */
        ~Vector();

        /**
         * @returns size_t la dimensione **usata** del vettore
         */
        size_t size() const;

        /**
         * @returns check se la dimensione utilizzata è 0
         */
        bool isEmpty() const;

        /**
         * @brief utilizzato per avere una copia dell'ultimo elemento del vettore,
         * se il vettore non ha elementi, crea un elemento di default
         *
         * @return T ultimo elemento dell'array
         */
        T back() const;

        /**
         * @brief aggiunge un elemento alla fine del vettore e fa una resize
         * dinamica del vettore secondo necessità utilizzando la doubling-halving
         *
         * @param element l'elemento da aggiungere
         */
        void push_back(T element);

        /**
         * @brief rimuove l'elemento in posizione index e lo ritorna
         * fa una resize del vettore secondo necessità utilizzando la doubling-halving
         * Se è vuoto ritorna l'elemento costruito di default del tipo dato
         *
         * @return T l'elemento rimosso
         */
        T pop_back();

        /**
         * @brief rimuove l'elemento in posizione index senza preservare l'ordine dei restanti elementi
         * se l'index è invalido ritorna l'elemento del costruttore di default
         *
         * @param index l'indice dell'elemento da rimuovere
         * @return T l'elemento rimosso
         */
        T remove(size_t index);

        /**
         * @brief ridimensiona l'array. Se lo spazio più piccolo, gli elementi con index maggiore sono troncati
         * tutti il resto degli elementi sono ricopiati
         *
         * @param size la nuova dimensione del vettore
         */
        void resize(size_t size);

        /**
         * @brief ridimensiona l'array per poter contenere SIZE elementi e assegna
         * il valore VAL in input per indici 0..SIZE-1.
         *
         * @param size la nuova dimensione del vettore
         * @param val il valore da assegnare ai nuovi elementi
         */
        void assign(size_t size, T val);

        /**
         * @brief  elimina tutto quanto contenuto nel vettore e ricostruisce
         * come il costruttore ()
         */
        void clear();

        /**
         * @brief copia tutto il contenuto di un altro vector nel vettore attuale
         *
         * @param other il vettore da copiare
         * @returns reference al vettore attuale
         */
        Vector<T> &operator=(const Vector<T> &other);

        T &operator[](const int index) const;
        T &at(const int index) const;
        int indexOf(T el);
    };

    template <class T>
    size_t Vector<T>::_getHigherPowerOfTwo(size_t n) {
        size_t x = 1;
        while (x <= n) {
            x <<= 1;
        }
        return x;
    }

    template <class T>
    void Vector<T>::_resize(size_t size, size_t newRealSize) {
        int endCopyIdx = size < size_ ? size : size_;  // minore fra i due
        size_ = size;
        T *new_space = new T[newRealSize];
        for (int i = 0; i < endCopyIdx; i++) {
            new_space[i] = data_[i];
        }
        delete[] data_;
        data_ = new_space;
        realSize_ = newRealSize;
    }

    template <class T>
    void Vector<T>::_copyFrom(const Vector<T> &other) {
        size_ = other.size_;
        realSize_ = other.realSize_;
        data_ = new T[realSize_];
        for (unsigned int i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    template <class T>
    Vector<T>::Vector(size_t size) {
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);
        data_ = new T[realSize_];
    }

    template <class T>
    Vector<T>::Vector()
        : Vector(0) {}

    template <class T>
    Vector<T>::Vector(const Vector<T> &other) {
        this->_copyFrom(other);
    }

    template <class T>
    Vector<T>::~Vector() {
        delete[] data_;
    }

    template <class T>
    size_t Vector<T>::size() const {
        return size_;
    }

    template <class T>
    bool Vector<T>::isEmpty() const {
        return size_ == 0;
    }

    template <class T>
    T &Vector<T>::operator[](const int index) const {
        return data_[index];
    }

    template <class T>
    T &Vector<T>::at(const int index) const {
        return data_[index];
    }

    template <class T>
    T Vector<T>::back() const {
        if (isEmpty()) return T();
        return data_[size_ - 1];
    }

    template <class T>
    void Vector<T>::push_back(T element) {
        if (size_ == realSize_) {
            _resize(size_, realSize_ * 2);
        }

        data_[size_] = element;
        size_ += 1;
    }

    template <class T>
    T Vector<T>::pop_back() {
        if (isEmpty()) return T();
        if (size_ == realSize_ / 4) {
            _resize(size_, realSize_ / 2);
        }
        size_ -= 1;
        return data_[size_];
    }

    template <class T>
    T Vector<T>::remove(size_t index) {
        if (index >= size_ or index < 0) return T();
        if (size_ == realSize_ / 4) {
            _resize(size_, realSize_ / 2);
        }
        T element = data_[index];
        size_ -= 1;
        data_[index] = data_[size_];
        return element;
    }

    template <class T>
    void Vector<T>::resize(size_t size) {
        size_t newRealSize = _getHigherPowerOfTwo(size);
        _resize(size, newRealSize);
    }

    template <class T>
    void Vector<T>::assign(size_t size, T val) {
        resize(size);
        for (unsigned int i = 0; i < size; i++) {
            data_[i] = val;
        }
        size_ = size;
    }

    template <class T>
    void Vector<T>::clear() {
        delete[] data_;
        realSize_ = 1;  // 1 per evitare errori nel *2 in push_back
        size_ = 0;
        data_ = new T[realSize_];
    }

    template <class T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
        if (this == &other) return *this;

        delete[] data_;
        this->_copyFrom(other);

        return *this;
    }

    template <class T>
    int Vector<T>::indexOf(T el) {
        for (unsigned int i = 0; i < size_; i++) {
            if (data_[i] == el) return i;
        }
        return -1;
    }
};  // namespace datastruct