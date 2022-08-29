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
            _setDisplayChar((char) enums::WallType::DOOROPEN);
        } else {
            _setDisplayChar((char) enums::WallType::DOORCLOSED);
        }
    }

    void DoorSegment::open() {
        Openable::open();
        _setDisplayChar((char) enums::WallType::DOOROPEN);
    }

    void DoorSegment::close() {
        Openable::close();
        _setDisplayChar((char) enums::WallType::DOORCLOSED);
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

    void DoorSegment::_setDisplayChar(char ch) {
        for (unsigned int i = 0; i < displayables_.size(); i++) {
            displayables_[i]->setDisplayChar(ch);
        }
    }
};  // namespace level
