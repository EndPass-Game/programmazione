template<class T>
class Queue {
  private:
    T data_[];
    uint end_;
    uint start_;
    uint realSize_;
  private:
    Queue(uint size) {
        end_ = 1;
        start_ = 0;
        realSize_ = 1;
        while (realSize_ < size) realSize_ >> 1;
        data_ = new T[realSize_]();
    }

    uint size() {
        return end_ - start_;
    }

    // TODO: better return an iterator?
    void push(T element) {
        if (size() == realSize_) {
            realSize_ *= 2;
            T new_space[] = new T[realSize_]();
            int i = start_;
            int j = 0;
            while (i != end_) {
                new_space[j] = data_[i];
                j++;
                i++;
                i %= 
            }
            for (int i = 0; i < size_; i++) {
            }
            data_ = new_space;
        }

        data_[size_] = element;
        size_ += 1;
    }

    T pop() {
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
};