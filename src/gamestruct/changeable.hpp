#pragma once
#include <mutex>


//Questa classe mantiene un oggetto che può cambiare nel tempo
//e ha una semplice interfaccia per vedere se è stato modificato,
//si può settare subito il suo ultimo valore, o se si lascia indefinito
//si potrà verificare che è il primo valore che lì'oggetto riceve da isFirstVal
template <class T>
class Changeable
{
private:
    //Contine il valore che aveva current prima di essere stato settato dall'ultimo setCurrent
    T last_;
    //Contiene il valore che è stato settato per ultimo da setCurrent
    T current_;
    //È true solo se last_ non ha un valore, cio'è quando l'oggetto è
    //inizializzato dal costruttore che non prende last come argomento
    bool firstValue_;
    //mutex per mantenere l'oggetto thread safe
    std::mutex mutex;

public:
    //Questo costruttore permette di inizializzare sia il valore corrente
    //che l'ultimo che ha avuto l'oggetto, essendo che last ha un valore
    //isFirstValue() sarà false
    Changeable(T last, T current);

    ~Changeable();

    //Questo costruttore inizializza solo il valore corrente
    //essendo che il valore vecchio è indefinito per nostra
    //isChange()=false, ma isFisrtVal()=true
    Changeable(T current);

    //da come risultato vero solo se è la classe non ha un vecchio valore
    //, ma solo il corrente
    bool isFirstValue();

    //ritorna true se l'oggetto è stato cambiato
    bool isChanged();

    //cambia il valore corrente dell'oggetto 
    //e cambia l'ultimo valore che l'oggetto ha avuto
    void setCurrent(T newVal);

    //ritorna penultimo valore preso da setCurrent
    T getLast();

    //ritorna l'ultimo valore preso da setCurrent
    T getCurrent();
};

template <class T>
Changeable<T>::Changeable(T last, T current) : last_(last), current_(current), firstValue_(false) {}
template <class T>
Changeable<T>::Changeable(T current) : last_(current), current_(current), firstValue_(true) {}

template <class T>
void Changeable<T>::setCurrent(T newVal)
{
    std::lock_guard<std::mutex> lock(mutex);
    firstValue_ = false;
    last_ = current_;
    current_ = newVal;
}

template <class T>
bool Changeable<T>::isChanged()
{
    std::lock_guard<std::mutex> lock(mutex);
    return last_ != current_;
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
    return last_;
}

template <class T>
T Changeable<T>::getCurrent()
{
    std::lock_guard<std::mutex> lock(mutex);
    return current_;
}
template <class T>
Changeable<T>::~Changeable(){

}