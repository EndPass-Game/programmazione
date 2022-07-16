#pragma once 

#include "datastruct/vector.hpp"

namespace loader {
    // questa classe carica tutti i file txt come assets di LIVELLO 
    // ossia in grado di generare un livello di gioco
    // all'interno di una directory 
    class DirectoryLoader {
      private:
        datastruct::Vector<char *> fileNames_;

        bool _isExtensionValid(const char *filename, const char *extension);
      public:
        // loads all valid files in the directory
        // assumes directory has the "/", only LINUX compatible.
        DirectoryLoader(const char *directory = "assets/");
        ~DirectoryLoader();

        const char *getRandomFileName();
    };
}; // namespace loader