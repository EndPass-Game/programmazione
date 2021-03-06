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
        if (isOpen_) {
            _setDisplayChar((char) enums::WallType::DOOROPEN);
        } else {
            _setDisplayChar((char) enums::WallType::DOORCLOSED);
        }
    }

    bool DoorSegment::isDoorOpen() const {
        return isOpen_;
    }

    void DoorSegment::openDoor() {
        isOpen_ = true;
        _setDisplayChar((char) enums::WallType::DOOROPEN);
    }

    void DoorSegment::closeDoor() {
        isOpen_ = false;
        _setDisplayChar((char) enums::WallType::DOORCLOSED);
    }

    void DoorSegment::setNextLevelIdx(int nextLevelIdx) {
        nextLevelIdx_ = nextLevelIdx;
    }

    int DoorSegment::getNextLevelIdx() const {
        return nextLevelIdx_;
    }

    enums::CollisionType DoorSegment::getCollisionType() {
        return enums::CollisionType::DOORSEGMENT;
    }

    void DoorSegment::_setDisplayChar(char ch) {
        for (unsigned int i = 0; i < displayables_.size(); i++) {
            displayables_[i]->setDisplayChar(ch);
        }
    }
}; // namespace level