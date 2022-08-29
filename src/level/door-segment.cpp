#include "level/door-segment.hpp"

#include "enums/wall-type.hpp"
namespace level {
    DoorSegment::DoorSegment()
        : DisplayableSegment(),
          Openable(false) {}

    DoorSegment::DoorSegment(const Segment &segment, enums::Direction facingDir, int nextLevelIdx, bool isOpen)
        : DisplayableSegment(segment),
          Openable(isOpen),
          facingDir_(facingDir),
          nextLevelIdx_(nextLevelIdx) {
        if (this->isOpen()) {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::DOOROPEN);
        } else {
            DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
        }
    }

    void DoorSegment::open() {
        Openable::open();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::DOOROPEN);
    }

    void DoorSegment::close() {
        Openable::close();
        DisplayableSegment::_setDisplayChar((char) enums::WallType::DOORCLOSED);
    }

    void DoorSegment::setNextLevelIdx(int nextLevelIdx) {
        nextLevelIdx_ = nextLevelIdx;
    }

    int DoorSegment::getNextLevelIdx() const {
        return nextLevelIdx_;
    }

    enums::Direction DoorSegment::getFacingDir() const {
        return facingDir_;
    }

    enums::CollisionType DoorSegment::getCollisionType() {
        return enums::CollisionType::DOORSEGMENT;
    }
};  // namespace level
