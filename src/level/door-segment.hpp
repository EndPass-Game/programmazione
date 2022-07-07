#pragma once

#include "gamestruct/position.hpp"
#include "level/wall-segment.hpp"

namespace level {
    class DoorSegment : public WallSegment {
        public:
            DoorSegment();
            DoorSegment(Position startPosition, enums::Direction direction, int length);
            ~DoorSegment();
            void render(WINDOW *win, bool force);
    };
}; // namespace level