#pragma once

#include "entities/enemy.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "manager/level.fwd.h"

namespace entities {
    class Shooter : public Enemy {
      private:
        int shootCoolDown_;
        int shootCoolDownMax_;

        Logger logger_;

      public:
        Shooter(Position spawnPos);

        /**
         * @brief controlla se la linea di tiro contro il player è libera
         */
        virtual bool canAttack(manager::Level *levelManager);

        void resetShootCoolDown();

        void ShootCoolDown();

        virtual void wander(Player *player) override;

        bool canShoot();

        void attack(manager::Level *levelManager) override;

        enums::Direction findShootDirection(manager::Level *levelManager, Position currPosition, Position playerPosition);
    };
}  // namespace entities