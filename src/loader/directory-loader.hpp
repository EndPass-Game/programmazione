#pragma once

#include "datastruct/vector.tpp"
#include "gamestruct/logger.hpp"

namespace loader {
    /**
     * @brief questa classe carica tutti i file txt come assets di LIVELLO
     * ossia in grado di generare un livello di gioco
     * all'interno di una directory
     */
    class DirectoryLoader {
      private:
        datastruct::Vector<char *> fileNames_;
        Logger logger_;

        /**
         * @brief valida l'estensione di `filename`
         *
         * @param filename il filename su cui si deve validare l'estensione
         * @param extension l'estensione che deve essere presente alla fine di filename
         * @return true se vale la condizione sopra
         */
        bool _isExtensionValid(const char *filename, const char *extension);

      public:
        /**
         * @brief carica tutti i file validi nella directory
         * presuppone che la directory abbia "/", compatibile solo con LINUX.
         */
        DirectoryLoader(const char *directory = "assets/");

        /**
         * @brief distruttore della classe DirectoryLoader
         * livera la memoria per tutti i filenames caricati
         */
        ~DirectoryLoader();

        /**
         * @returns tutti i file txt contenuti nella directory
         */
        datastruct::Vector<char *> getFileNames();

        /**
         * @returns un file txt random contenuto nella directory
         */
        const char *getRandomFileName();
    };
};  // namespace loader
