#pragma once 

#include <cstdlib>

#include "level/wall-segment.hpp"
#include "loader/load-object.hpp"
#include "gamestruct/position.hpp"

namespace loader {
    class PlayerPosition: public LoadObject<Position> {
      public:
        void load(FILE *file) override;
    };
} // namespace loader