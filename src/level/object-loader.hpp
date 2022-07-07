#pragma once 

#include "datastruct/vector.hpp"
#include "level/wall-segment.hpp"
#include "level/door-segment.hpp"

namespace level {
    // carica oggetti di un livello di gioco da un file di testo   
    // struttura del file: 
    // [numero muri]
    // [carattere muro] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [numero porta]
    // [carattere porta] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [coordinate chiave]
    class ObjectLoader {
        FILE *file_;
      public:
        ObjectLoader(const char *filename);
        ~ObjectLoader();

        // si assume che il file sia ben formato (come in descrizione)
        // in più i valori non creino overflow in seguito nel rendering
        // e nell'ordine giusto
        datastruct::Vector<WallSegment *> *ObjectLoader::loadWalls();
    }
}; // namespace level