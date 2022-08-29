#pragma once

#include <mutex>

#include "entities/enemy.hpp"
#include "gamestruct/position.hpp"

namespace entities {
    class Kamikaze : public Enemy {
      private:

      public:
        Kamikaze();
        Kamikaze(Position spawnPos);

        virtual enums::EnemyType getEnemyType() override;
    };
}  // namespace entities