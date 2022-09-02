#pragma once

#include <mutex>

#include "entities/enemy.hpp"
#include "gamestruct/position.hpp"
#include "manager/level.fwd.h"

namespace entities {
    class Kamikaze : public Enemy {
      private:

      public:
        Kamikaze();
        Kamikaze(Position spawnPos);

        void attack(manager::Level *levelManager) override;

        bool canAttack(manager::Level *levelManager) override;
    };
}  // namespace entities