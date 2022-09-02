#pragma once

#include <mutex>

#include "manager/level.fwd.h"
#include "entities/enemy.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/logger.hpp"
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

        bool canShoot();

        void attack(manager::Level *levelManager) override;


        // TODO simo
        virtual bool canAttack(manager::Level *levelManager) override {return false;};
    };
}  // namespace entities