#pragma once 

#include <ncurses.h>

#include "level/displayable-segment.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"

namespace level {
    // classe che rappresenta un segmento di muri
    // inoltre i segmenti di muri sono oggetto di collisione per oggetti o entità. e collidable permette ciò
    class WallSegment: public DisplayableSegment {
      private:
        char _getWallCharacter(enums::Direction direction);
      public: 
        // segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla
        WallSegment(); 
        WallSegment(Position start_position, enums::Direction direction, int length);

        virtual enums::CollisionType getCollisionType();
    }; // class WallSegment
}; // namespace level