template<class T>
class Vector {
  private:
    T data_[];
    uint size_;
    uint realSize_;

    uint _getHigherPowerOfTwo(uint n) {
        int x = 1;
        while (x < size_) x >> 1;
        return x;
    }

  private:
    Vector(uint size) {
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);    
        data_ = new T[realSize_]();
    }

    Vector(): Vector(0) {}

    uint size() {
        return size_;
    }

    // TODO: better return an iterator?
    void push_back(T element) {
        if (size_ == realSize_) {
            realSize_ *= 2;
            T new_space[] = new T[realSize_]();
            for (int i = 0; i < size_; i++) {
                new_space[i] = data_[i];
            }
            data_ = new_space;
        }

        data_[size_] = element;
        size_ += 1;
    }

    T pop_back() {
        if (size_ == realSize_ / 4) {
            realSize_ /= 2;
            T new_space[] = new T[realSize_]();
            for (int i = 0; i < size_; i++) {
                new_space[i] = data_[i];
            }
            data_ = new_space;
        }

        size_ -= 1;
        T element = data_[size_];
        return element;
    }

    // 
    void resize(uint size) {
        realSize_ = _getHigherPowerOfTwo(size); 
        int endIndex;
        if (size < realSize_) endIndex = size;
        else endIndex = realSize_;   

        T new_space[] = new T[realsSize_]();
        for (int i = 0; i < endIndex) {
            new_space[i] = data_[i];
        }
        data_ = new_space;
    }
};