/*
Dati
1. mappa successiva
2. porta aprta
3. muri
4. entità
5. prima porta
6. stanze

Funzioni:




*/
#pragma once

#include <ncurses.h>

#include "datastruct/vector.hpp"
#include "entities/player.hpp"
#include "gamestruct/log-queue.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.hpp"
#include "level/collidable.hpp"
#include "level/level.hpp"
#include "loader/directory-loader.hpp"
#include "manager/manager-settings.hpp"

namespace manager {
    /// Level manager: contiene tutte gli oggetti che vengono mostrati
    /// nel gioco
    class Level {
      private:
        datastruct::Vector<level::Level *> levels_;
        Player *player_;
        StateWatcher<int> *levelIdx_;
        loader::DirectoryLoader *dirLoader_;
        LogQueue *logQueue_;

        Logger logger_;

        /// @brief aggiunge un nuovo livello al vettore levels_
        /// @param direction il livello aggiunto dovrà avere una porta nella direzione opposta a quella indicata
        /// @returns l'index del livello creato
        int _addLevel(enums::Direction direction = enums::Direction::NONE);

      public:
        Level();
        ~Level();

        /// @brief getter del player_
        Player *getPlayer();

        /// @brief getter del levelIdx_, usato per indicare il livello corrente
        level::Level *getLevel();

        /// @brief getter del logQueue_, usato per mostrare i messaggi di log
        /// allo schermo del giocatore
        LogQueue *getLogQueue();

        /// @brief stampa a schermo il livello scelto, se non è presente tale livello (indice invalido)
        /// allora ritorna false, altrimenti true;
        /// @param level: è l'indice del livello in cui andare
        void goToLevel(int level);

        /// @brief calcola un oggetto di collisione al punto indicato
        /// @param pos: indica la posizione in cui guardare per il check della collisione
        /// @return l'oggetto della collisione
        level::Collidable *getCollision(Position pos);

        /// @brief permette al giocatore di sparare nell'ultima direzione
        /// in cui si muoveva.
        void playerShoot();

        /// @brief genera un nuovo livello, se il livello corrente è stato completato
        /// @param door: la porta a cui linkare il nuovo livello
        void generateLevel(level::DoorSegment *door);

        /// @brief renderizza gli oggetti del livello su schermo
        void render(WINDOW *win, bool force);
    };
}  // namespace manager
