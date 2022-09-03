#include "loader/objects/local-door.hpp"

namespace loader {
    void LocalDoor::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);
        loadedObjects_->resize(numeroPorte);
        for (int i = 0; i < numeroPorte; i++) {
            int direction;
            Position startPos;
            int length;
            int id;
            fscanf(file, "%d %d %d %d %d\n", &startPos.riga, &startPos.colonna, &direction, &length, &id);
            level::LocalDoor *door = new level::LocalDoor(
                level::Segment(startPos, (enums::Direction) direction, length),
                id
            );
            this->loadedObjects_->at(i) = door;
        }
    };
}  // namespace loader
