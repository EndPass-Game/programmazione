/*
#include "changeable.hpp"
#include "position.hpp"

template <class T>
Changeable<T>::Changeable(T last,T current):last(last),current(current){}

template <class T>
Changeable<T>::Changeable(){}


template <class T>
void Changeable<T>::setCurrent(T newVal){
    if(current!=newVal or last!=current){
        last=current;
        current=newVal;
    }
}

template <class T>
bool Changeable<T>::isChanged(){
    return last!=current;
}

template <class T>
T Changeable<T>::getLast(){
    return last;
}

template <class T>
T Changeable<T>::getCurrent(){
    return current;
}
void fun_(){
    Changeable<Position> pos;
}
*/