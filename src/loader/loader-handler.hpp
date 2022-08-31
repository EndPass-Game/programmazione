#pragma once

#include "datastruct/vector.tpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "loader/objects/artifact.hpp"
#include "loader/objects/door-segment.hpp"
#include "loader/objects/enemy.hpp"
#include "loader/objects/local-door.hpp"
#include "loader/objects/power.hpp"
#include "loader/objects/wall-segment.hpp"

namespace loader {
    // Carica TUTTI gli oggetti di un livello di gioco da un file di testo
    // struttura del file:
    // [numero di muri]
    // pos.x pos.y direzione tipo-di-angolo lunghezza
    // [numero di porte]
    // pos.x pos.y direzione  direzione-rispetto-al-centro lunghezza player-pos-x player-pos-y
    // [numero di local doors]
    // pos.x pos.y direzione lunghezza id
    // [numero di artefatti]
    // pos.x e pos.y e vita del artefatto
    // [numero di poteri]
    // pos.x e pos.y e id-associato-local-dor
    // una volta richiesto un oggetto, deve essere eliminato dal chiamante.
    // [numero di nemici]
    // pos.x e pos.y del nemico
    //
    // WARNING: Se il file è mal configurato, o non esiste proprio ci sarà un errore di runtime
    // ----FATALE---- che farà crashare il programma.
    struct LoaderHandler {
        FILE *file;
        WallSegment wallLoader;
        DoorSegment doorLoader;
        LocalDoor localDoorLoader;
        Artifact artifactLoader;
        Power powerLoader;
        Enemy enemyLoader;
        LoaderHandler(const char *filename);
        ~LoaderHandler();

        void load();
    };
};  // namespace loader
