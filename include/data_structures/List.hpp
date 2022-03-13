//TODO: test ed eliminare le funzioni in più che non servono

template<class T>
class Stack {
  private:
    Data *first;
    Data *last;
    uint size;

  public:
    struct Data{
        Data(Data* prev, Data* next,T dato):prev(prev),next(next),dato(dato) {}
        Data *prev;
        Data *next;
        T dato;
    };

    T back(){
        if(last==nullptr)return nullptr;
        else return last->dato;
    }

    T front(){
        if(first==nullptr)return nullptr;
        else return first->dato;
    }

    void push_front(T element){
        if(size==0){
            first=last=new Data{nullptr,nullptr,element};
        }else{
            Data* wasfirst=first;
            first=new Data{nullptr,wasfirst,element};
            wasfirst->prev=first;
        }
        size++;
    }

    void pop_front(){
        if(size==0) throw;
        Data* sf= first->next;
        delete first;
        first=sf;
        size--;
    }

    void push_back(T element){
        if(size==0){
            first = new Data{nullptr, nullptr, element};
        }
        else
        {
            Data *waslast = last;
            last = new Data{waslast,nullptr, element};
            waslast->prev = last;
        }
        size++;
    }
    void pop_back(){
        if(size==0) throw;
        Data* sl= last->next;
        delete last;
        last=sl;
        size--;
    }

    Data* search(T element){
        Data *tmp;
        tmp=first;
        while(tmp != nullptr){
            if(tmp->dato == element){
                return tmp;
            }
            tmp=tmp->next;
        }
        return nullptr;
    }
};