#include "loader/loader-handler.hpp"

namespace loader {
    LoaderHandler::LoaderHandler(const char *filename) {
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("File %s not found\n", filename);
            exit(1);
        }

        wallLoader = new WallSegment();
        doorLoader = new DoorSegment();
        playerPosLoader = new PlayerPosition();
        artifactLoader = new Artifact();
        powerLoader = new Power();

        wallLoader->load(file);
        doorLoader->load(file);
        playerPosLoader->load(file);
        artifactLoader->load(file);
        powerLoader->load(file);
    }
    
    LoaderHandler::~LoaderHandler() {
        fclose(file);
        delete wallLoader;
        delete doorLoader;
        delete playerPosLoader;
        delete artifactLoader;
        delete powerLoader;
    }
}; // namespace loader