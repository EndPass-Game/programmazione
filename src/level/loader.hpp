#pragma once 

#include "datastruct/vector.hpp"
#include "level/wall-segment.hpp"
#include "level/door-segment.hpp"

namespace level {
    // carica TUTTI gli oggetti di un livello di gioco da un file di testo   
    // struttura del file: 
    // [numero muri]
    // [carattere muro] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [numero porta]
    // [carattere porta] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [coordinate chiave]
    // una volta richiesto un oggetto, deve essere eliminato dal chiamante.
    class Loader {
        FILE *file_;
        bool isWallTransferred_; // se l'ownership dei muri è stata trasferita 
        datastruct::Vector<WallSegment *> *wallSegments_; 
        bool isDoorTransferred_; // se l'ownership delle porte è stata trasferita
        datastruct::Vector<DoorSegment *> *doorSegments_; 
        // TODO(ang|simo): gestire anche gli altri oggetti da loaddare
        // l'ordine di caricamento è importante, quindi non posso rendere questi metodi pubblici
        void _loadWalls(); 
        void _loadDoors();
      public:
        Loader(const char *filename);
        ~Loader();

        // si assume che il file sia ben formato (come in descrizione)
        // in più i valori non creino overflow in seguito nel rendering
        // e nell'ordine giusto
        datastruct::Vector<WallSegment *> *getLoadedWalls();
        datastruct::Vector<DoorSegment *> *getLoadedDoors();
    };
}; // namespace level