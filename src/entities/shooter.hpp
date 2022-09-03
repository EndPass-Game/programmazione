#pragma once

#include <mutex>

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
        Shooter();
        Shooter(Position spawnPos);

        void resetShootCoolDown();

        void ShootCoolDown();

        virtual void wander(Player *player) override;

        bool canShoot();

        void attack(manager::Level *levelManager) override;

        virtual bool canAttack(manager::Level *levelManager) override;

        enums::Direction findShootDirection(manager::Level *levelManager, Position currPosition, Position playerPosition);
    };
}  // namespace entities