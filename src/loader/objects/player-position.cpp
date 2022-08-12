#include "loader/objects/player-position.hpp"

namespace loader {
    void PlayerPosition::load(FILE *file) {
        LoadObject::resetTransferred();

        const int kNumeroPosizioni = 1;
        this->loadedObjects_->resize(kNumeroPosizioni);
        Position *pos = new Position();
        fscanf(file, "%d %d\n", &pos->riga, &pos->colonna);
        this->loadedObjects_->at(0) = pos;
    };
}  // namespace loader
