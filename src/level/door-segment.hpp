#pragma once

#include <ncurses.h>

#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
namespace level{

    class DoorSegment: public DisplayableSegment {
    protected:
        int nextLevelIdx_; // -1 default per livello inesistente
        bool isOpen_=false;

    public:
        DoorSegment();
        DoorSegment(Position start_position, 
            enums::Direction direction, 
            int length,
            int nextLevel = -1, // quando è una porta d'uscita che non porta a nessun livello 
            bool isOpen = false);

        bool isDoorOpen() const;

        virtual enums::CollisionType getCollisionType() override;
    };
}; // namespace level