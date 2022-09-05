#pragma once

#include <ncurses.h>

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.fwd.h"

namespace entities {
    /**
     * @brief rappresenta un generico nemico
     */
    class Enemy : public Entity {
      private:
        int coolDown_;
        int coolDownMax_;
        Logger logger_;

      public:
        /**
         * @param spawnPos posizione nell oschermo del nemico
         * @param attack il valore di attacco del nemico
         * @param c il carattere printato a schermo rappresentante il nemico
         */
        Enemy(Position spawnPos, int attack, char c);

        /**
         * @brief applica un movimento generico per l'enemy
         *
         * @param player sarà utilizzato per applicare euristiche
         * sulal posizione
         */
        virtual void wander(Player *player);

        void resetCoolDown();

        void moveCoolDown();

        bool canMove();

        void setPosition(Position pos);

        virtual void act(manager::Level *levelManager) override;
    };
}  // namespace entities
