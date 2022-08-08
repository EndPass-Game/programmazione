#include "loader/objects/artifact.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Artifact::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroArtefatti;
        fscanf(file, "%d", &numeroArtefatti);
        this->_loadedObjects->resize(numeroArtefatti);
        for (int i = 0; i < numeroArtefatti; i++) {
            int artifactHealth;
            Position startPosition;
            fscanf(file, "%d %d %d\n", &startPosition.riga, &startPosition.colonna, &artifactHealth);
            collectables::Artifact *artifact = new collectables::Artifact(artifactHealth, startPosition);
            this->_loadedObjects->at(i) = artifact;
        }
    };
}  // namespace loader
