#include "loader/loader-handler.hpp"

namespace loader {
    LoaderHandler::LoaderHandler(const char *filename)
        : wallLoader(),
          doorLoader(),
          localDoorLoader(),
          artifactLoader(),
          powerLoader(),
          enemyLoader() {
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("File %s not found\n", filename);
            exit(1);
        }
    }

    LoaderHandler::~LoaderHandler() {
        fclose(file);
    }

    void LoaderHandler::load() {
        rewind(file);  // resetta il file descriptor all'inizio del file
        wallLoader.load(file);
        doorLoader.load(file);
        localDoorLoader.load(file);
        artifactLoader.load(file);
        powerLoader.load(file);
        enemyLoader.load(file);
    }
};  // namespace loader