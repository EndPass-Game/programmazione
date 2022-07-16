#pragma once 

#include "datastruct/vector.hpp"
#include "level/wall-segment.hpp"
#include "level/door-segment.hpp"
#include "loader/loaders.hpp" // WallLoader, DoorLoader, ArtifactLoader, PlayerPosLoader
namespace loader {
    // Carica TUTTI gli oggetti di un livello di gioco da un file di testo   
    // struttura del file: 
    // [numero di muri]
    // pos.x pos.y direzione lunghezza
    // [numero di porte]
    // pos.x pos.y direzione lunghezza
    // pos.x e pos.y del giocatore
    // pos.x e pos.y e vita del artefatto
    // una volta richiesto un oggetto, deve essere eliminato dal chiamante.
    // 
    // WARNING: Se il file è mal configurato, o non esiste proprio ci sarà un errore di runtime 
    // ----FATALE---- che farà crashare il programma.
    // 
    // ESEMPIO DI UN FILE LIVELLO VALIDO: 
    // 4
    // 0 0 4 59
    // 5 59 2 11
    // 16 59 3 59
    // 16 0 1 11
    // 2
    // 0 59 2 5
    // 0 0 2 5
    // 1 1
    // 0 0 0
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