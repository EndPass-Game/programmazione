#pragma once

#include "datastruct/vector.hpp"

namespace loader {
    // questa è una classe astratta che descrive gli oggetti che possono essere caricati da un file di testo
    template <typename T>
    class LoadObject {
      protected:
        datastruct::Vector<T> loadedObjects_;

      public:
        LoadObject();
        virtual ~LoadObject();

        datastruct::Vector<T> getLoadedObjects();
        virtual void load(FILE *file) = 0;
        void resetTransferred();
    };

    template <typename T>
    LoadObject<T>::LoadObject()
        : loadedObjects_() {}

    template <typename T>
    LoadObject<T>::~LoadObject() = default;

    template <typename T>
    datastruct::Vector<T> LoadObject<T>::getLoadedObjects() {
        return loadedObjects_;
    }
};  // namespace loader
