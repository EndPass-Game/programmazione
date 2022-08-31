#pragma once

#include "datastruct/vector.tpp"
#include "gamestruct/logger.hpp"

namespace loader {
    // questa classe carica tutti i file txt come assets di LIVELLO
    // ossia in grado di generare un livello di gioco
    // all'interno di una directory
    class DirectoryLoader {
      private:
        datastruct::Vector<char *> fileNames_;
        Logger logger_;
        bool _isExtensionValid(const char *filename, const char *extension);

      public:
        // loads all valid files in the directory
        // assumes directory has the "/", only LINUX compatible.
        DirectoryLoader(const char *directory = "assets/");
        ~DirectoryLoader();

        // @returns tutti i file txt contenuti nella directory
        datastruct::Vector<char *> getFileNames();

        // @returns un file txt random contenuto nella directory
        const char *getRandomFileName();
    };
};  // namespace loader