#pragma once

#include <cstdio>  // FILE

#include "datastruct/vector.tpp"

namespace loader {
    /**
     * @brief Classe astratta che descrive gli oggetti che possono essere caricati da un file di testo
     *
     * @tparam T il tipo di oggetto che si vuole caricare
     */
    template <typename T>
    class LoadObject {
      protected:
        bool isTransferred_;
        datastruct::Vector<T *> *loadedObjects_;

      public:
        /**
         * @brief Costruttore della classe LoadObject
         */
        LoadObject();

        /**
         * @brief Distruttore della classe LoadObject
         */
        virtual ~LoadObject();

        /**
         * @brief ritorna l'array degli oggetti caricati
         *
         * WARNING: quando questa funzione è chiamata, l'onere di liberare la memoria occupata
         * è lasciata al chiamante.
         *
         * NOTE: è possibile chiamare questa funzione un unica volta per loading
         * altrimenti sarà ritornato un nullptr
         */
        datastruct::Vector<T *> *getLoadedObjects();

        /**
         * @brief la funzione astratta per caricare i dati da un file di testo
         *
         * @param file il FILE da cui leggere i dati
         */
        virtual void load(FILE *file) = 0;

        /**
         * @brief reset dello stato transferred, permette di caricare nuovamente i dati
         */
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
