#pragma once
#include <mutex>


//Questa classe mantiene un oggetto che può cambiare nel tempo
//e ha una semplice interfaccia per vedere se è stato modificato

template <class T>
class Changeable
{
private:
    //ultimo valore dell'elemento
    T last_;
    // elemento corrente
    T current_;
    // vera solo quando è chiamato il costruttore senza last
    bool firstValue_;
    //mutex per mantenere l'oggetto thread safe
    std::mutex mutex;
public:
    //inizializziamo anche con il valore vecchio
    //isFirstValue sarà false e isChange darà last!=current come risultato
    Changeable(T last, T current);
    //Costruttore che setta solo il valore corrente
    //isChange darà false ma isFirstVAlue darà true
    Changeable(T current);

    //se è la prima volta che è stato inizializzato
    // da true come risultato
    bool isFirstValue();

    //ritorna true se l'oggetto è stato cambiato
    bool isChanged();

    //mette current=last e current=newVal
    void setCurrent(T newVal);

    //ritorna penultimo valore preso da setCurrent
    T getLast();

    //ritorna l'ultimo valore preso da setCurrent
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