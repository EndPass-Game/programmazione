#include "loader/loaders.hpp"

#include "enums/direction.hpp"

namespace loader {

    void WallLoader::load(FILE *file) {
        int numeroMuri;
        fscanf(file, "%d", &numeroMuri);
        this->_loadedObjects->resize(numeroMuri);
        for(int i = 0; i < numeroMuri; i++) {
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%d %d %d %d\n" , &startPosition.riga, &startPosition.colonna, &direction , &length);
            level::WallSegment *wall = new level::WallSegment(startPosition, (enums::Direction)direction, length);
            (*this->_loadedObjects)[i] = wall;
        }
    }

    void DoorLoader::load(FILE *file) {
        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);
        this->_loadedObjects->resize(numeroPorte);
        for(int i = 0; i < numeroPorte; i++) {
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%d %d %d %d\n" , &startPosition.riga, &startPosition.colonna , &direction , &length);
            level::DoorSegment *door = new level::DoorSegment(startPosition, (enums::Direction)direction, length);
            (*this->_loadedObjects)[i] = door;
        }
    };

    void PlayerPosLoader::load(FILE *file) {
        int numeroPosizioni = 1;
        this->_loadedObjects->resize(numeroPosizioni);
        Position *pos = new Position();
        fscanf(file, "%d %d\n", &pos->riga, &pos->colonna);
        (*this->_loadedObjects)[0] = pos;
    };


    void ArtifactLoader::load(FILE *file) {
        int numeroArtefatti;
        fscanf(file, "%d", &numeroArtefatti);
        this->_loadedObjects->resize(numeroArtefatti);
        for(int i = 0; i < numeroArtefatti; i++) {
            int artifactHealth;
            Position startPosition;
            fscanf(file, "%d %d %d\n" , &startPosition.riga, &startPosition.colonna, &artifactHealth);
            Artifact *artifact = new Artifact(/* // TODO(simo|ang): startPosition*/);
            (*this->_loadedObjects)[i] = artifact;
        }
    };

}; // namespace loaders
