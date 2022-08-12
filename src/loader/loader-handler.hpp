#pragma once

#include "datastruct/vector.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "loader/objects/artifact.hpp"
#include "loader/objects/door-segment.hpp"
#include "loader/objects/player-position.hpp"
#include "loader/objects/power.hpp"
#include "loader/objects/wall-segment.hpp"
namespace loader {
    // Carica TUTTI gli oggetti di un livello di gioco da un file di testo
    // struttura del file:
    // [numero di muri]
    // pos.x pos.y direzione lunghezza tipo di angolo
    // [numero di porte]
    // pos.x pos.y direzione lunghezza
    // pos.x e pos.y del giocatore
    // [numero di artefatti]
    // pos.x e pos.y e vita del artefatto
    // [numero di poteri]
    // pos.x e pos.y del potere
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
    // 16 0 1 12
    // 2
    // 0 59 2 5
    // 0 0 2 5
    // 1 1
    // 1
    // 3 3 3
    struct LoaderHandler {
        FILE *file;
        WallSegment wallLoader;
        DoorSegment doorLoader;
        PlayerPosition playerPosLoader;
        Artifact artifactLoader;
        Power powerLoader;
        LoaderHandler(const char *filename);
        ~LoaderHandler();

        void load();
    };
};  // namespace loader