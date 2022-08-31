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
        /**
         * @brief costruisce un nuovo segmento door-segment
         */
        DoorSegment();

        /**
         * @brief carica gli oggetti per door-segment
         *
         * @param file File descriptor da cui caricare di door-segment
         */
        void load(FILE *file) override;

        /**
         * @brief getter per hasNorthDoor_
         */
        bool hasNorthDoor() const;

        /**
         * @brief getter per hasEastDoor_
         */
        bool hasEastDoor() const;

        /**
         * @brief getter per hasSouthDoor_
         */
        bool hasSouthDoor() const;

        /**
         * @brief getter per hasWestDoor_
         */
        bool hasWestDoor() const;

        /**
         * @brief getter per playerPositions_
         */
        datastruct::Vector<Position> getPlayerPositions() const;
    };
}  // namespace loader
