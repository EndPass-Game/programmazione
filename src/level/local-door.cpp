#include "level/local-door.hpp"

#include "enums/wall-type.hpp"

namespace level {
    LocalDoor::LocalDoor(const Segment &segment, bool isOpen)
        : DisplayableSegment(segment),
          Openable(isOpen) {
        if (this->isOpen()) {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::EMPTY);
        } else {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
        }
    }
    
    void LocalDoor::open() {
        Openable::open();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::EMPTY);
    }
    
    void LocalDoor::close() {
        Openable::close();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
    }
}  // namespace level