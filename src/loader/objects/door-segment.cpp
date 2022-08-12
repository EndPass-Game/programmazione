#include "loader/objects/door-segment.hpp"

#include <iostream>

#include "gamestruct/position.hpp"

namespace loader {
    void DoorSegment::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);

        // se il numero delle porte è minore di 2, si dovrebbe fare distinzione fra le porte iniziali (con sola entrata)
        // e le porte con entrata e uscite, con l'attuale impolementazione delle porte non si possiede
        // questa astrazione.
        // per evitare questo problema poniamo l'INVARIANTE che tutti i livelli debbano avere almeno 2 porte
        // in modo da avere sempre una entrata o un uscita (oppure più uscite nel caso)
        if (numeroPorte < 2) {
            std::cerr << "Errore: il numero di porte deve essere maggiore di 1" << std::endl;
            exit(1);
        }

        this->_loadedObjects->resize(numeroPorte);
        for (int i = 0; i < numeroPorte; i++) {
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%d %d %d %d\n", &startPosition.riga, &startPosition.colonna, &direction, &length);
            level::DoorSegment *door = new level::DoorSegment(startPosition, (enums::Direction) direction, length);
            this->_loadedObjects->at(i) = door;
        }
    };
}  // namespace loader
