#pragma once 

#include <cstdlib> 

#include "collectables/artifact.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "loader/load-object.hpp"
#include "gamestruct/position.hpp"

namespace loader {
    class WallLoader: public LoadObject<level::WallSegment> {
      public:
        void load(FILE *file) override;
    };

    class DoorLoader: public LoadObject<level::DoorSegment> {
      public:
        void load(FILE *file) override;
    };

    class ArtifactLoader: public LoadObject<Artifact> {
      public:
        void load(FILE *file) override;
    };

    class PlayerPosLoader: public LoadObject<Position> {
      public:
        void load(FILE *file) override;
    };
}; // namespace loader