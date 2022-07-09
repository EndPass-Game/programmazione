#include "level/wall-segment.hpp"

#include <ncurses.h>

#include "enums/wall-type.hpp"

namespace level {
    WallSegment::WallSegment() : 
        DisplayableSegment() {}

    WallSegment::WallSegment(Position startPosition, enums::Direction direction, int length) {
        WallSegment::DisplayableSegment(startPosition, direction, length);

        char wallCharacter = _getWallCharacter(direction);
        for (unsigned int i = 0; i < displayables_.size(); i++) {
            if (displayables_[i]->getPosition() == startPosition) {
                displayables_[i]->setDisplayChar((char) enums::WallType::ANGLE);
            } else {
                displayables_[i]->setDisplayChar(wallCharacter);
            }
        }
    }

    char WallSegment::_getWallCharacter(enums::Direction direction){
        enums::WallType type;
        switch (direction) {
            case enums::Direction::UP:
            case enums::Direction::DOWN:
                type = enums::WallType::VERT;
                break;
            case enums::Direction::LEFT:
            case enums::Direction::RIGHT:
                type = enums::WallType::HORIZ;
                break;
            default:
                type = enums::WallType::EMPTY;
                break;
        }
        return (char) type;
    }

    enums::CollisionType WallSegment::getCollisionType() {
        return enums::CollisionType::WALLSEGMENT;
    }

}; // namespace level