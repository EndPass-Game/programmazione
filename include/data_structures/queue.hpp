template<class T>
class Queue {
  private:
    T data_[];
    uint end_;
    uint start_;
    uint realSize_;

    uint _getHigherPowerOfTwo(uint n) {
        int x = 1;
        while (x < size_) x >> 1;
        return x;
    }

    void _resize(uint size) {
        uint newSize = _getHigherPowerOfTwo(size); 
        T new_space[] = new T[newSize]();
        int i = start_;
        int j = 0;
        while (i != end_ && j < newSize) {
            new_space[j] = data_[i];
            j++;
            i++;
            if (i == realSize_) i -= realSize_;
        }
        realSize_ = newSize;
        delete[] data_;
        data_ = new_space;
    }

  public:
    Queue(uint size) {
        end_ = 1;
        start_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);
        data_ = new T[realSize_]();
    }
    Queue(): Queue(0) {}

    uint size() const {
        return end_ - start_;
    }

    uint isEmpty() const {
        return end_ == start_;
    }

    // TODO: better return an iterator?
    void push(T element) {
        if (size() == realSize_) {
            _resize(size());
        }

        data_[end_] = element;
        end_ += 1;
        if (end_ == realSize_) end_ -= realSize_;
    }

    T pop() {
        if (isEmpty()) throw;

        if (size() == realSize_ / 4) {
            _resize(size());
        }

        T element = data_[size_];
        start_ += 1;
        if (start_ == realSize_) start_ -= realSize_;
        return element;
    }
};