#include "loader/loaders.hpp"

#include <iostream> // cerr

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
            int angleType;
            fscanf(file, "%d %d %d %d %d\n" , &startPosition.riga, &startPosition.colonna, &direction , &length,&angleType);
            level::WallSegment *wall = new level::WallSegment(startPosition, (enums::Direction)direction, length,(enums::WallAngleType) angleType);
            this->_loadedObjects->at(i) = wall;
        }
    }

    void DoorLoader::load(FILE *file) {
        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);

        // se il numero delle porte è minore di 2, si dovrebbe fare distinzione fra le porte iniziali (con sola entrata) 
        // e le porte con entrata e uscite, con l'attuale impolementazione delle porte non si possiede 
        // questa astrazione.
        // per evitare questo problema poniamo l'INVARIANTE che tutti i livelli debbano avere almeno 2 porte
        // in modo da avere sempre una entrata o un uscita (oppure più uscite nel caso) 
        if (numeroPorte < 2) {
            std::cerr << "Errore: il numero di porte deve essere maggiore di 1" << std::endl;
            exit(1); 
        }

        this->_loadedObjects->resize(numeroPorte);
        for(int i = 0; i < numeroPorte; i++) {
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%d %d %d %d\n" , &startPosition.riga, &startPosition.colonna , &direction , &length);
            level::DoorSegment *door = new level::DoorSegment(startPosition, (enums::Direction)direction, length);
            this->_loadedObjects->at(i) = door;
        }
    };

    void PlayerPosLoader::load(FILE *file) {
        const int kNumeroPosizioni = 1;
        this->_loadedObjects->resize(kNumeroPosizioni);
        Position *pos = new Position();
        fscanf(file, "%d %d\n", &pos->riga, &pos->colonna);
        this->_loadedObjects->at(0) = pos;
    };


    void ArtifactLoader::load(FILE *file) {
        int numeroArtefatti;
        fscanf(file, "%d", &numeroArtefatti);
        this->_loadedObjects->resize(numeroArtefatti);
        for(int i = 0; i < numeroArtefatti; i++) {
            int artifactHealth;
            Position startPosition;
            fscanf(file, "%d %d %d\n" , &startPosition.riga, &startPosition.colonna, &artifactHealth);
            Artifact *artifact = new Artifact(artifactHealth, startPosition);
            this->_loadedObjects->at(i) = artifact;
        }
    };

    void PowerLoader::load(FILE *file) {
        int numeroPoteri;
        fscanf(file, "%d", &numeroPoteri);
        this->_loadedObjects->resize(numeroPoteri);
        for(int i = 0; i < numeroPoteri; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n" , &startPosition.riga, &startPosition.colonna);
            Power *power = new Power(startPosition);
            this->_loadedObjects->at(i) = power;
        }
    };

}; // namespace loaders
