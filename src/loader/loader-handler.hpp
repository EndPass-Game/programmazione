#pragma once 

#include "datastruct/vector.hpp"
#include "level/wall-segment.hpp"
#include "level/door-segment.hpp"
#include "loader/loaders.hpp" // WallLoader, DoorLoader, ArtifactLoader, PlayerPosLoader
namespace loader {
    // carica TUTTI gli oggetti di un livello di gioco da un file di testo   
    // struttura del file: 
    // [numero muri]
    // [carattere muro] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [numero porta]
    // [carattere porta] ((int) pos.x, (int) pos.y) (int) direzione (int) lunghezza
    // [coordinate chiave]
    // una volta richiesto un oggetto, deve essere eliminato dal chiamante.
    struct LoaderHandler {
        FILE *file;
        WallLoader *wallLoader;
        DoorLoader *doorLoader;
        PlayerPosLoader *playerPosLoader;
        ArtifactLoader *artifactLoader;
        LoaderHandler(const char *filename);
        ~LoaderHandler();
    };
}; // namespace level