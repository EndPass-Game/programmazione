#include "loader/objects/player-position.hpp"

namespace loader {
    void PlayerPosition::load(FILE *file) {
        const int kNumeroPosizioni = 1;
        this->_loadedObjects->resize(kNumeroPosizioni);
        Position *pos = new Position();
        fscanf(file, "%d %d\n", &pos->riga, &pos->colonna);
        this->_loadedObjects->at(0) = pos;
    };
} // namespace loader
