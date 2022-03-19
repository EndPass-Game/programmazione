#pragma once


namespace datastruct {

} // namespace data struct

template<class T>
class LinkedList {
  public:
    struct Data;
  private:
    Data *first_;
    Data *last_;
    size_t size_;

  public:
    struct Data {
        Data *prev;
        Data *next;
        T dato;
        Data(Data* prev, Data* next,T dato):
            prev(prev),
            next(next),
            dato(dato) {}
    };


    T back() {
        if (last_ == nullptr) return T();
        else return last_->dato;
    }

    T front() {
        if (first_ == nullptr) return T();
        else return first_->dato;
    }

    void push_front(T element) {
        if(size_ == 0){
            first_=last_=new Data{nullptr,nullptr,element};
        }else{
            Data *wasfirst = first_;
            first_ = new Data{nullptr,wasfirst,element};
            wasfirst->prev=first_;
        }
        size_++;
    }

    void pop_front() {
        if(size_ == 0) return;
        Data *sf = first_->next;
        delete first_;
        first_ = sf;
        size_--;
    }

    void push_back(T element) {
        if(size_ == 0) {
            first_ = new Data{nullptr, nullptr, element};
            last_ = first_;
        }
        else
        {
            Data *waslast = last_;
            last_ = new Data{waslast,nullptr, element};
            waslast->next = last_;
        }
        size_++;
    }

    void pop_back() {
        if (size_ == 0) return;
        Data *sl = last_->prev;
        delete last_;
        last_ = sl;
        size_--;
    }

    size_t getSize() const {
        return size_;
    }

    Data *search(T element){
        Data *tmp = first_;
        while(tmp != nullptr){
            if(tmp->dato == element){
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }
};