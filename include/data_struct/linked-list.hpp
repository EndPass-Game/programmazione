#pragma once
namespace datastruct {
template<class T>
class LinkedList {
  public:
    struct Data;
  private:
    Data *first_;
    Data *last_;
    size_t size_;

  public:
    LinkedList() {
        first_ = nullptr;
        last_ = nullptr;
        size_ = 0;
    }

    ~LinkedList() {
        Data *head = first_;
        while (head != nullptr) {
            Data *curr = head;
            head = head->next;
            delete curr;
        }
    }

    struct Data {
        Data *prev;
        Data *next;
        T dato;
        Data(Data* prev, Data* next,T dato):
            prev(prev),
            next(next),
            dato(dato) {}
    };


    T back() const {
        if (last_ == nullptr) return T();
        else return last_->dato;
    }

    T front() {
        if (first_ == nullptr) return T();
        else return first_->dato;
    }

    void push_front(T element) {
        if(size_ == 0){
            first_ = new Data(nullptr, nullptr, element);
            last_ = first_;
        }else{
            Data *wasfirst = first_;
            first_ = new Data(nullptr, wasfirst, element);
            wasfirst->prev=first_;
        }
        size_++;
    }

    void pop_front() {
        if (size_ == 0) return;
        Data *toDelete = first_;
        first_ = toDelete->next;
        if (first_ != nullptr) first_->prev = nullptr;
        else last_ = nullptr; 
        size_--;
        delete toDelete;
    }

    void push_back(T element) {
        if(size_ == 0) {
            first_ = new Data(nullptr, nullptr, element);
            last_ = first_;
        } else {
            Data *waslast = last_;
            last_ = new Data(waslast, nullptr, element);
            waslast->next = last_;
        }
        size_++;
    }

    void pop_back() {
        if (size_ == 0) return;
        Data *toDelete = last_;
        last_ = toDelete->prev;
        if (last_ != nullptr) last_->next = nullptr;
        else first_ = nullptr; // non c'è niente nella lista
        size_--;
        delete toDelete;
    }

    size_t size() const {
        return size_;
    }

    Data *search(T element){
        Data *tmp = first_;
        while(tmp != nullptr) {
            if(tmp->dato == element){
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }
};
} // namespace datastruct
