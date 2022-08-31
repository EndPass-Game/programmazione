#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "datastruct/vector.tpp"
#include "entities/enemy.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
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
         * @param loaderHandler il loader che contiene i dati del livello
         */
        Level(loader::LoaderHandler *loader);

        /**
         * @brief Construct a new Level object
         *
         * @param loader il loader che contiene i dati del livello
         * @param direction specifica di caricare solo livelli in questa direzione
         * @param oldLevelIdx il collegamento al livello precedente
         */
        Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx);

        /**
         * @brief Distruttore che elimina ogni oggetto contenuto nel livello
         */
        ~Level();

        /**
         * @brief renderizza il contenuto del livello
         * @param force se true rirenderizza anche quelli non modificati
         */
        void render(WINDOW *win, bool force, manager::Level *levelmanager);

        /**
         * @brief cancella tutto quanto printato su schermo
         */
        void clear(WINDOW *win);

        // REGION --------- TODO: discutere di questa parte
        datastruct::Vector<collectables::Power *> getPowers();
        datastruct::Vector<collectables::Artifact *> getArtifacts();

        void addBullet(weapon::Bullet *bullet);
        void renderBullets(WINDOW *win, manager::Level *levelmanager);

        void deleteEnemy(Collidable *collision, WINDOW *win);
        void deletePower(int i);
        void deleteArtifact(int i);

        void enemiesAttack(WINDOW *win, manager::Level *levelManager);
        void renderEnemies(WINDOW *win, manager::Level *levelManager);
        // ENDREGION --------- TODO: discutere di questa parte

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
