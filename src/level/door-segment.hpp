#pragma once

#include <ncurses.h>

#include "enums/direction.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
namespace level {

    class DoorSegment : public DisplayableSegment {
      private:
        int nextLevelIdx_;  // -1 default per livello inesistente
        bool isOpen_ = false;

        // private helper function to set character of segment to ch
        void _setDisplayChar(char ch);

      public:
        DoorSegment();
        DoorSegment(Position start_position, enums::Direction direction, int length,
                    int nextLevelIdx = -1,  // quando è una porta d'uscita che non porta a nessun livello
                    bool isOpen = false);

        bool isDoorOpen() const;

        void openDoor();

        void closeDoor();

        void setNextLevelIdx(int nextLevelIdx);

        int getNextLevelIdx() const;

        virtual enums::CollisionType getCollisionType() override;
    };
};  // namespace level
