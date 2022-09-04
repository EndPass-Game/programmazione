#pragma once

#include <ncurses.h>

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "enums/enemyType.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.fwd.h"

// Attualmente questa classe contiene un esempio di nemico
// che si muove e attacca il giocatore.
// Dovrebbe essere sostituito da un sistema per gestire ogni
// possibile nemico. (quindi un manager)
// oppure una factory per costruire il nemico specifico
namespace entities {
    class Enemy : public Entity {
      private:
        int coolDown_;
        int coolDownMax_;
        Logger logger_;

      public:
        Enemy(char c);
        Enemy(Position spawnPos, int attack, char c);

        // int getDamage();

        void setPosition(Position pos);

        virtual void wander(Player *player);

        void resetCoolDown();

        void moveCoolDown();

        bool canMove();

        virtual bool canAttack(manager::Level *levelManager) = 0;

        virtual void act(manager::Level *levelManager) override;
    };
}  // namespace entities
