#pragma once

#include <cstdlib>

#include "entities/enemy.hpp"
#include "entities/kamikaze.hpp"
#include "entities/shooter.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class Enemy : public LoadObject<entities::Enemy> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader