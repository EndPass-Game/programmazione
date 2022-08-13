#include "loader/objects/artifact.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Artifact::load(FILE *file) {
        int numeroArtefatti;
        fscanf(file, "%d", &numeroArtefatti);
        loadedObjects_.resize(numeroArtefatti);
        for (int i = 0; i < numeroArtefatti; i++) {
            int artifactHealth;
            Position startPosition;
            fscanf(file, "%d %d %d\n", &startPosition.riga, &startPosition.colonna, &artifactHealth);
            collectables::Artifact artifact = collectables::Artifact(artifactHealth, startPosition);
            loadedObjects_[i] = artifact;
        }
    };
}  // namespace loader
