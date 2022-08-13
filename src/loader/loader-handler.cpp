#include "loader/loader-handler.hpp"

namespace loader {
    LoaderHandler::LoaderHandler(const char *filename)
        : wallLoader(),
          doorLoader(),
          artifactLoader(),
          powerLoader() {
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
        wallLoader.load(file);
        doorLoader.load(file);
        artifactLoader.load(file);
        powerLoader.load(file);
    }
};  // namespace loader