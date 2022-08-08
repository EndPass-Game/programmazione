#include "loader/objects/power.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Power::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroPoteri;
        fscanf(file, "%d", &numeroPoteri);
        this->_loadedObjects->resize(numeroPoteri);
        for (int i = 0; i < numeroPoteri; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            collectables::Power *power = new collectables::Power(startPosition);
            this->_loadedObjects->at(i) = power;
        }
    };
}  // namespace loader
