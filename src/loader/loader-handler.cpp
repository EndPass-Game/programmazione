#include "loader/loader-handler.hpp"

namespace loader {
    LoaderHandler::LoaderHandler(const char *filename) {
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("File %s not found\n", filename);
            exit(1);
        }

        wallLoader = new WallLoader();
        doorLoader = new DoorLoader();
        playerPosLoader = new PlayerPosLoader();
        artifactLoader = new ArtifactLoader();
        powerLoader = new PowerLoader();

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