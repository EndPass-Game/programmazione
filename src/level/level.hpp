#pragma once

#include "entities/enemy.fwd.h"
#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "datastruct/vector.hpp"
#include "entities/shooter.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "entities/weapon/bullet.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "loader/loader-handler.hpp"

namespace level {
    // contenere tutti i oggetti utili per il singolo livello
    class Level {
      private:
        Position lastPlayerPosition_;
        datastruct::Vector<DisplayableSegment *> segment_;
        datastruct::Vector<collectables::Artifact *> artifacts_;
        datastruct::Vector<collectables::Power *> powers_;
        datastruct::Vector<entities::Enemy *> enemies_;
        datastruct::Vector<weapon::Bullet *> bullets_;
        datastruct::Vector<Position> playerPositions_;
        int numOfDoors_;  // numero di porte nel livello

        Logger logger_;

      public:
        Level(loader::LoaderHandler *loader);
        Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx);

        ~Level();

        // restituisce la posizione dell'ultimo player
        Position getLastPlayerPosition();

        // setta la posizione dell'ultimo player
        void setLastPlayerPosition(Position pos);

        // @brief renderizza il contenuto del livello
        // @param force se true rirenderizza anche quelli non modificati
        void render(WINDOW *win, bool force, manager::Level *levelmanager);

        // cancella tutto quanto printato su schermo
        void clear(WINDOW *win);

        // @returns true se la posizione è vuota, false altrimenti
        bool isPositionEmpty(Position pos, manager::Level *levelManager);

        void addBullet(weapon::Bullet *bullet);
        void renderBullets(WINDOW *win, manager::Level *levelmanager);

        void renderEnemies(WINDOW *win, manager::Level *levelManager);
        // @returns l'oggetto di collisione alla data posizione
        Collidable *getCollision(Position pos, manager::Level *levelManager) const;

        /**
         * @brief elimina il collidable in input.
         * presuppone che sia dei seguenti tipi:
         * - artifact
         * - power
         * - enemy
         * 
         * E che questi siano presenti nella lista corrispondente in questo oggetto
         */
        void deleteCollidable(Collidable *collidable);
    };
};  // namespace level