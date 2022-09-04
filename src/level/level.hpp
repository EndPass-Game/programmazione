#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "datastruct/vector.tpp"
#include "entities/enemy.fwd.h"
#include "entities/entity.fwd.h"
#include "entities/player.hpp"
#include "entities/shooter.hpp"
#include "entities/weapon/bullet.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "level/local-door.hpp"
#include "loader/loader-handler.hpp"

namespace level {
    /**
     * @brief Questa classe contiene tutti gli oggetti utili per il singolo livello
     */
    class Level {
      private:
        /**
         * @brief ultima posizione del player in questo livello
         * utilizzato principalmente per avere consistenza di posizione
         * ad ogni cambio di livello
         */
        Position lastPlayerPosition_;
        Player *player_;

        datastruct::Vector<DisplayableSegment *> segment_;
        datastruct::Vector<collectables::Artifact *> artifacts_;
        datastruct::Vector<collectables::Power *> powers_;
        datastruct::Vector<entities::Enemy *> enemies_;
        datastruct::Vector<weapon::Bullet *> bullets_;
        datastruct::Vector<Position> playerPositions_;
        datastruct::Vector<LocalDoor *> localDoors_;
        int numOfDoors_;  // numero di porte nel livello

        Logger logger_;

      public:
        /**
         * @brief Costruttore di un livello
         *
         * @param player il player del manager
         * @param loaderHandler il loader che contiene i dati del livello
         */
        Level(loader::LoaderHandler *loader, Player *player);

        /**
         * @brief Construct a new Level object
         *
         * @param loader il loader che contiene i dati del livello
         * @param player il player del manager
         * @param direction specifica di caricare solo livelli in questa direzione
         * @param oldLevelIdx il collegamento al livello precedente
         */
        Level(loader::LoaderHandler *loader, Player *player, enums::Direction direction, int oldLevelIdx);

        /**
         * @brief Distruttore che elimina ogni oggetto contenuto nel livello
         */
        ~Level();

        /**
         * @brief renderizza il contenuto del livello
         * @param force se true rirenderizza anche quelli non modificati
         */
        void render(WINDOW *win, bool force);

        /**
         * @brief cancella tutto quanto printato su schermo
         */
        void clear(WINDOW *win);

        void addBullet(weapon::Bullet *bullet);

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

        /**
         * @brief muove tutti gli oggetti che si devono muovere
         * all'interno del livello
         */
        void act(manager::Level *levelManager);

        /**
         * @brief opens the local door with the same id as input
         * @param id id of the local door to open
         */
        void openLocalDoor(int id);

        bool isComplete();
        Collidable *getCollision(Position pos) const;
        void openAllDoors();
        void setLastPlayerPosition(Position pos);
        Position getLastPlayerPosition();
    };
};  // namespace level
