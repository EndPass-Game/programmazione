#include "loader/objects/power.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Power::load(FILE *file) {
        int numeroPoteri;
        fscanf(file, "%d", &numeroPoteri);
        loadedObjects_.resize(numeroPoteri);
        for (int i = 0; i < numeroPoteri; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            collectables::Power power = collectables::Power(startPosition);
            loadedObjects_[i] = power;
        }
    };
}  // namespace loader
