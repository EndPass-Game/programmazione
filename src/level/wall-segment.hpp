#pragma once 

#include <ncurses.h>

#include "level/displayable-segment.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
#include "enums/wall-angle.hpp"

namespace level {
    // classe che rappresenta un segmento di muri
    // inoltre i segmenti di muri sono oggetto di collisione per oggetti o entità. e collidable permette ciò
    class WallSegment: public DisplayableSegment {
      private:
        enums::WallAngleType angleType;
        char _getWallCharacter(enums::Direction direction);
        bool _isAngle(int positionOffset);
      public: 
        // segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla
        WallSegment(); 
        WallSegment(Position start_position, enums::Direction direction, int length,enums::WallAngleType angle);

        virtual enums::CollisionType getCollisionType();
    }; // class WallSegment
}; // namespace level