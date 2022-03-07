#pragma once
#include <mutex>


//Questa classe mantiene un oggetto che può cambiare nel tempo
//e ha una semplice interfaccia per vedere se è stato modificato

template <class T>
class Changeable
{
private:
    T last_;
    T current_;
    bool firstValue_;
    std::mutex mutex;
public:
    Changeable(T last, T current);
    Changeable(T current);

    bool isFirstValue();

    bool isChanged();

    void setCurrent(T newVal);
    T getLast();
    T getCurrent();
};

template <class T>
Changeable<T>::Changeable(T last,T current):last_(last),current_(current),firstValue_(false){}
template <class T>
Changeable<T>::Changeable(T current):last_(current),current_(current),firstValue_(true){}

template <class T>
void Changeable<T>::setCurrent(T newVal)
{
    std::lock_guard<std::mutex> lock(mutex);
    firstValue_=false;
    last_ = current_;
    current_ = newVal;
}

template <class T>
bool Changeable<T>::isChanged()
{
    std::lock_guard<std::mutex> lock(mutex);
    return  last_!=  current_;
}

template <class T>
bool Changeable<T>::isFirstValue()
{
    std::lock_guard<std::mutex> lock(mutex);
    return firstValue_;
}

template <class T>
T Changeable<T>::getLast()
{
    std::lock_guard<std::mutex> lock(mutex);
    return  last_;
}

template <class T>
T Changeable<T>::getCurrent()
{
    std::lock_guard<std::mutex> lock(mutex);
    return  current_;
}