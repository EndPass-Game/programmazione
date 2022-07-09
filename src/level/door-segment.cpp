#include "level/door-segment.hpp"
#include "enums/wall-type.hpp"
namespace level {
    DoorSegment::DoorSegment() : 
        DisplayableSegment() {}

    DoorSegment::DoorSegment(Position start_position, 
      enums::Direction direction, 
      int length, 
      int nextLevelIdx, 
      bool isOpen): 
      DisplayableSegment(start_position, direction, length),
      nextLevelIdx_(nextLevelIdx), isOpen_(isOpen) { 
        for (unsigned int i = 0; i < displayables_.size(); i++) {
            if (isOpen_) {
                displayables_[i]->setDisplayChar((char) enums::WallType::DOOROPEN);
            } else {
                displayables_[i]->setDisplayChar((char) enums::WallType::DOORCLOSED);
            }
        }
    }

    bool DoorSegment::isDoorOpen() const {
        return isOpen_;
    }

    enums::CollisionType DoorSegment::getCollisionType() {
        return enums::CollisionType::DOORSEGMENT;
    }
}; // namespace level