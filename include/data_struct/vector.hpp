
namespace datastruct {
template<class T>
class Vector {
  private:
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

  public:
    Vector(size_t size) {
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);    
        data_ = new T[realSize_];
    }

    Vector(): Vector(0) {}
    ~Vector() {
        delete [] data_;
    }

    size_t size() const {
        return size_;
    }

    size_t isEmpty() const {
        return size_ == 0;
    }

    void push_back(T element) {
        if (size_ == realSize_) {
            resize(size_);
        }

        data_[size_] = element;
        size_ += 1;
    }

    T pop_back() {
        if (isEmpty()) return T();
        if (size_ == realSize_ / 4) {
            resize(size_);
        }
        size_ -= 1;
        return data_[size_];
    }

    T remove(size_t index) {
        if (index >= size_ or index < 0) return T();
        if (size_ == realSize_ / 4) {
            resize(size_);
        }
        T element = data_[index];
        size_ -= 1;
        data_[index] = data_[size_];
        return element;
    }

    void resize(size_t size) {
        realSize_ = _getHigherPowerOfTwo(size); 
        int endIndex = size < realSize_ ? size : realSize_;

        T *new_space = new T[realSize_];
        for (int i = 0; i < endIndex; i++) {
            new_space[i] = data_[i];
        }
        delete [] data_;
        data_ = new_space;
    }

    T &operator [](const int index) const {
        return data_[index];
    }
};

} // namespace datastruct