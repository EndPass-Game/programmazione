#pragma once

#include <mutex>

#include "entities/enemy.hpp"
#include "gamestruct/position.hpp"

namespace entities {
    class Shooter : public Enemy {
      private:
        int shootCoolDown_;
        int shootCoolDownMax_;

      public:
        Shooter();
        Shooter(Position spawnPos);

        void resetShootCoolDown();

        void ShootCoolDown();

        bool canShoot();

        virtual enums::EnemyType getEnemyType() override;
    };
}  // namespace entities