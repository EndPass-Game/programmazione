#pragma once

#include <cstdlib>

#include "entities/enemy.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class Enemy : public LoadObject<entities::Enemy> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader
