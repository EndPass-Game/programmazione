#pragma once
#include <stddef.h>  // size_t
#pragma once
namespace datastruct {
    /**
     * @brief Implementazione di una coda che utilizza un array dinamico doubling-halving
     * sono tenuti in considerazione solamente gli indici di inizio e fine coda, in modo 
     * che si possa avere una coda circolare
     * @tparam T il tipo di oggetto che la coda deve contenere
     */
    template <class T>
    class Queue {
      private:
        size_t end_;  // idx fine della coda
        size_t start_;  // idx inizio della coda
        size_t size_;
        size_t realSize_;
        T *data_;

        size_t _getHigherPowerOfTwo(size_t n);
        void _resize(size_t size);

      public:
        /**
         * @brief costruisce una nuova Queue object con dimensione size
         * 
         * @param size la dimensione della Queue
         */
        Queue(size_t size);

        /**
         * @brief Costruisce una queue di dimensione 0
         */
        Queue();

        /**
         * @brief distruttore di queue, libera la memoria allocata
         */
        ~Queue();

        /**
         * @returns size_t la dimensione **usata** della queue
         * È differente rispetto alla size effettivamente allocata
         */
        size_t size() const;

        /**
         * @returns check se la dimensione utilizzata è 0
         */
        size_t isEmpty() const;

        /**
         * @brief aggiunge un elemento alla fine della coda e fa una resize
         * dinamica della coda secondo necessità utilizzando la doubling-halving
         * 
         * @param element l'elemento da aggiungere
         */
        void push(T element);

        /**
         * @brief ritorna l'ultimo elemento in coda
         * Non sono fatti nessun check sulla size, attenzione
         * ad invalid reads.
         */
        T &last();

        /** 
         * @brief ritorna il primo elemento in coda
         * Non sono fatti nessun check sulla size, attenzione
         * ad invalid reads.
         */
        T &first();

        /**
         * @brief rimuove l'elemento in posizione index
         * se la coda è vuota viene ritornato l'elemento costruito di default
         */
        T pop();

        /**
         * @returns T& l'elemento in posizione index
         */
        T &operator[](const int index) const;
        
        /**
         * @returns T& l'elemento in posizione index
         */
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
