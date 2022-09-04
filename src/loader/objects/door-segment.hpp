#pragma once

#include <cstdlib>

#include "gamestruct/position.hpp"
#include "level/door-segment.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class DoorSegment : public LoadObject<level::DoorSegment> {
      private:
        datastruct::Vector<Position> playerPositions_;
        bool hasNorthDoor_;
        bool hasEastDoor_;
        bool hasSouthDoor_;
        bool hasWestDoor_;

        /**
         * @brief resetta ogni has*Door_ a false
         */
        void _resetMetaData();

        /**
         * @brief a seconda della direzione setta has*Door_ a true
         * @example se facingDir == UP, setta hasNorthDoor_ a true
         */
        void _setMetaData(enums::Direction facingDirection);

      public:
        DoorSegment();

        void load(FILE *file) override;

        bool hasNorthDoor() const;

        bool hasEastDoor() const;

        bool hasSouthDoor() const;

        bool hasWestDoor() const;

        datastruct::Vector<Position> getPlayerPositions() const;
    };
}  // namespace loader
