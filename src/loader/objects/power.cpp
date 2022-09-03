#include "loader/objects/power.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Power::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroPoteri;
        fscanf(file, "%d", &numeroPoteri);
        this->loadedObjects_->resize(numeroPoteri);
        for (int i = 0; i < numeroPoteri; i++) {
            Position startPosition;
            int id;
            fscanf(file, "%d %d %d\n", &startPosition.riga, &startPosition.colonna, &id);
            collectables::Power *power = new collectables::Power(startPosition, id);
            this->loadedObjects_->at(i) = power;
        }
    };
}  // namespace loader
