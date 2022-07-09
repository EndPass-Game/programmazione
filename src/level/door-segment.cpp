#include "level/door-segment.hpp"
#include "enums/wall-type.hpp"
namespace level {
    DoorSegment::DoorSegment() : 
        DisplayableSegment() {}

    DoorSegment::DoorSegment(Position start_position, 
      enums::Direction direction, 
      int nextLevelIdx, 
      int length, 
      bool isOpen): nextLevelIdx_(nextLevelIdx), isOpen_(isOpen) { 
        DoorSegment::DisplayableSegment(start_position, direction, length); 

        for (unsigned int i = 0; i < displayables_.size(); i++) {
            if (isOpen_) {
                displayables_[i]->setDisplayChar((char) enums::WallType::DOOROPEN);
            } else {
                displayables_[i]->setDisplayChar((char) enums::WallType::DOORCLOSED);
            }
        }
    }

    enums::CollisionType DoorSegment::getCollisionType() {
        return enums::CollisionType::DOORSEGMENT;
    }
}; // namespace level