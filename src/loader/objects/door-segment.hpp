#pragma once

#include <cstdlib>

#include "level/door-segment.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class DoorSegment : public LoadObject<level::DoorSegment> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader
