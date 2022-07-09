#include "level/door-segment.hpp"

namespace level
{
    DoorSegment::DoorSegment(Position start_position, enums::Direction direction, int length, int nextLevel, bool isOpen)
        : WallSegment(start_position, direction, length), goToLevel_(nextLevel), isOpen_(isOpen)
    { }

    enums::CollisionType DoorSegment::getCollisionType()
    {
        if (isOpen_)
            return enums::CollisionType::DOOR;
        else
            return enums::CollisionType::DOORCLOSED;
    }

    char DoorSegment::chooseWallCharacter(enums::Direction direction, Position pos)
    {
        if (isOpen_)
            return '.';
        else
            return '#';
    }

}; // namespace level