#pragma once 

#include "datastruct/vector.hpp"

namespace loader {
    // questa è una classe astratta che descrive gli oggetti che possono essere caricati da un file di testo
    template <typename T>
    class LoadObject {
      protected:
        bool _isTransferred; 
        datastruct::Vector<T *> *_loadedObjects;
      public: 
        LoadObject();
        virtual ~LoadObject();
        datastruct::Vector<T *> *getLoadedObjects();
        virtual void load(FILE *file) = 0; 
    };


    template <typename T>
    LoadObject<T>::LoadObject() {
        _isTransferred = false;
        _loadedObjects = new datastruct::Vector<T *>();
    }

    template <typename T>
    LoadObject<T>::~LoadObject() {
        if (!_isTransferred) {
            for (unsigned int i = 0; i < _loadedObjects->size(); i++) {
                delete (*_loadedObjects)[i];
            }
            delete _loadedObjects;
        }
    }

    // WARNING: quando questa funzione è chiamata, l'onere di liberare la memoria occupata
    // è lasciata al chiamante. 
    template <typename T>
    datastruct::Vector<T *> *LoadObject<T>::getLoadedObjects() {
        if (!_isTransferred) {
            _isTransferred = true;
            return _loadedObjects;
        } else {
            return nullptr;
        }
    }
}; // namespace loader