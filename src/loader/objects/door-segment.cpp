#include "loader/objects/door-segment.hpp"

#include <iostream>

#include "enums/direction.hpp"
#include "gamestruct/position.hpp"
#include "level/segment.hpp"
namespace loader {
    DoorSegment::DoorSegment()
        : LoadObject<level::DoorSegment>() {
        _resetMetaData();
    }

    void DoorSegment::_resetMetaData() {
        hasNorthDoor_ = false;
        hasEastDoor_ = false;
        hasSouthDoor_ = false;
        hasWestDoor_ = false;
    }

    void DoorSegment::_setMetaData(enums::Direction facingDirection) {
        switch (facingDirection) {
            case enums::Direction::UP:
                hasNorthDoor_ = true;
                break;
            case enums::Direction::RIGHT:
                hasEastDoor_ = true;
                break;
            case enums::Direction::DOWN:
                hasSouthDoor_ = true;
                break;
            case enums::Direction::LEFT:
                hasWestDoor_ = true;
                break;
            default:
                break;
        }
    }

    void DoorSegment::load(FILE *file) {
        LoadObject::resetTransferred();
        _resetMetaData();

        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);

        // se il numero delle porte è minore di 2, si dovrebbe fare distinzione fra le porte iniziali (con sola entrata)
        // e le porte con entrata e uscite, con l'attuale impolementazione delle porte non si possiede
        // questa astrazione.
        // per evitare questo problema poniamo l'INVARIANTE che tutti i livelli debbano avere almeno 2 porte
        // in modo da avere sempre una entrata o un uscita (oppure più uscite nel caso)
        // inoltre per avere consistenza con i movimenti del giocatore, poniamo un massimo di 4 porte per stanza
        if (numeroPorte < 2 || numeroPorte > 4) {
            std::cerr << "Errore: il numero di porte deve essere maggiore di 1 e minore di 5" << std::endl;
            exit(1);
        }

        this->loadedObjects_->resize(numeroPorte);
        for (int i = 0; i < numeroPorte; i++) {
            int direction;
            Position startPosition;
            int length;
            int facingDir;
            fscanf(file, "%d %d %d %d %d\n", &startPosition.riga, &startPosition.colonna, &direction, &length, &facingDir);
            level::DoorSegment *door = new level::DoorSegment(
                level::Segment(startPosition, (enums::Direction) direction, length),
                (enums::Direction) facingDir
            );
            _setMetaData((enums::Direction) facingDir);

            this->loadedObjects_->at(i) = door;
        }
    };

    bool DoorSegment::hasNorthDoor() const {
        return hasNorthDoor_;
    }

    bool DoorSegment::hasEastDoor() const {
        return hasEastDoor_;
    }

    bool DoorSegment::hasSouthDoor() const {
        return hasSouthDoor_;
    }

    bool DoorSegment::hasWestDoor() const {
        return hasWestDoor_;
    }
}  // namespace loader
