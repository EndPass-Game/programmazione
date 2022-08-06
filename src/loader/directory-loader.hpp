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
        // carica tutti i nomi validi di una directory
        // assume che il separatore di directory sia "/", solo compatibile con LINUX.
        DirectoryLoader(const char *directory = "assets/");
        ~DirectoryLoader();

        const char *getRandomFileName();

        // ritorna tutti i filenames all'interno di fileNames_ terminati da '\0'
        char[] getAllFilenames();
    };
}; // namespace loader