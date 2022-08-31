#pragma once

#include <cstdio>  // FILE

#include "datastruct/vector.tpp"

namespace loader {
    // questa è una classe astratta che descrive gli oggetti che possono essere caricati da un file di testo
    template <typename T>
    class LoadObject {
      protected:
        bool isTransferred_;
        datastruct::Vector<T *> *loadedObjects_;

      public:
        LoadObject();
        virtual ~LoadObject();

        // WARNING: quando questa funzione è chiamata, l'onere di liberare la memoria occupata
        // è lasciata al chiamante.
        datastruct::Vector<T *> *getLoadedObjects();
        virtual void load(FILE *file) = 0;
        void resetTransferred();
    };

    template <typename T>
    LoadObject<T>::LoadObject()
        : isTransferred_(false), loadedObjects_(new datastruct::Vector<T *>()) {}

    template <typename T>
    LoadObject<T>::~LoadObject() {
        if (!isTransferred_) {
            for (unsigned int i = 0; i < loadedObjects_->size(); i++) {
                delete loadedObjects_->at(i);
            }
        }
        delete loadedObjects_;
    }

    template <typename T>
    datastruct::Vector<T *> *LoadObject<T>::getLoadedObjects() {
        if (!isTransferred_) {
            isTransferred_ = true;
            return loadedObjects_;
        } else {
            return nullptr;
        }
    }

    template <typename T>
    void LoadObject<T>::resetTransferred() {
        isTransferred_ = false;
    }
};  // namespace loader
