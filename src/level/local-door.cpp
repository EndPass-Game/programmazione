#include "level/local-door.hpp"

#include "enums/wall-type.hpp"

namespace level {
    LocalDoor::LocalDoor(const Segment &segment, int id, bool isOpen)
        : DisplayableSegment(segment),
          Openable(isOpen),
          id_(id) {
        if (this->isOpen()) {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::EMPTY);
        } else {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
        }
    }

    int LocalDoor::getId() {
        return id_;
    }
    
    void LocalDoor::open() {
        Openable::open();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::EMPTY);
    }
    
    void LocalDoor::close() {
        Openable::close();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
    }

    enums::CollisionType LocalDoor::getCollisionType() {
        if (this->isOpen()) {
            return enums::CollisionType::NONE;
        } else {
            return enums::CollisionType::WALLSEGMENT;  // si comporta come un semplice muro se è chiuso
        }
    }
}  // namespace level
