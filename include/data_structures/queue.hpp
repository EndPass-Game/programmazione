#include <stdexcept>
template<class T>
class Queue {
  private:
    uint end_;
    uint start_;
    uint size_;
    uint realSize_;
    T *data_;

    uint _getHigherPowerOfTwo(uint n) {
        uint x = 1;
        while (x <= size_) {
            x <<= 1;
            if (x == 0) throw std::overflow_error("can't handle bigger size"); 
        }
        return x;
    }

    void _resize(uint size) {
        uint newSize = _getHigherPowerOfTwo(size); 
        uint minSize = size_ < newSize ? size_ : newSize;
        T *new_space = new T[newSize];
        for (uint i = start_, j = 0; j < minSize; i++, j++) {
            if (i == realSize_) i -= realSize_;
            new_space[j] = data_[i];
        }
        delete[] data_;
        data_ = new_space;
        realSize_ = newSize;
        start_ = 0;
        end_ = size_;
    }

    void _debugPrint() {
        for (uint i = start_, j = 0; j < size_; i++, j++) {
            if (i == realSize_) i -= realSize_;
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
        printf("DEBUG: start=%d end=%d, realsize=%d, size=%d\n", end_, realSize_, size_);
    }
  public:
    Queue(uint size) {
        end_ = 0;
        start_ = 0;
        size_ = 0;
        realSize_ = _getHigherPowerOfTwo(size);
        data_ = new T[realSize_];
    }
    Queue(): Queue(0) {}
    ~Queue() {
        delete[] data_;
    }

    uint size() const {
        return size_;
    }

    uint isEmpty() const {
        return size_ == 0;
    }

    // TODO: better return an iterator?
    void push(T element) {
        if (size_ == realSize_) {
            _resize(size_);
        }
        data_[end_] = element;
        end_ += 1;
        size_ += 1;
        if (end_ == realSize_) end_ -= realSize_;

    }

    T pop() {
        if (isEmpty()) throw;

        if (size_ == realSize_ / 4) {
            _resize(size_);
        }

        T element = data_[start_];
        start_ += 1;
        size_ -= 1;
        if (start_ == realSize_) start_ -= realSize_;
        return element;
    }
};