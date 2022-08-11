#pragma once

#include <cstdlib>

#include "gamestruct/position.hpp"
#include "level/wall-segment.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class PlayerPosition : public LoadObject<Position> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader