#pragma once

#include <cstdlib>

#include "level/wall-segment.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class WallSegment : public LoadObject<level::WallSegment> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader