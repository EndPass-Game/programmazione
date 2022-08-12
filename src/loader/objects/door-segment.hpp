#pragma once

#include <cstdlib>

#include "level/door-segment.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class DoorSegment : public LoadObject<level::DoorSegment> {
      private:
        bool hasNorthDoor_;
        bool hasEastDoor_;
        bool hasSouthDoor_;
        bool hasWestDoor_;

        void _resetMetaData();
        void _setMetaData(enums::Direction facingDirection);

      public:
        DoorSegment();
        void load(FILE *file) override;

        bool hasNorthDoor() const;
        bool hasEastDoor() const;
        bool hasSouthDoor() const;
        bool hasWestDoor() const;
    };
}  // namespace loader
