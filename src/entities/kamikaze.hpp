#pragma once

#include <mutex>

#include "entities/enemy.hpp"
#include "gamestruct/position.hpp"
#include "manager/level.fwd.h"

namespace entities {
    class Kamikaze : public Enemy {
      public:
        Kamikaze(Position spawnPos);

        virtual void wander(Player *player) override;

        void attack(manager::Level *levelManager) override;

        /**
         * @brief Controlla l'area circostante il kamikaze alla ricerca del player
         */
        bool canAttack(manager::Level *levelManager);
    };
}  // namespace entities