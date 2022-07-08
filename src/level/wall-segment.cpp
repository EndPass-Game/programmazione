#include "level/wall-segment.hpp"

#include <ncurses.h>

#include "enums/wall-type.hpp"

namespace level {
    WallSegment::WallSegment() : 
        Segment() {}

    WallSegment::WallSegment(Position startPosition, enums::Direction direction, int length) : 
      Segment(startPosition, direction, length) {
        // scegliendo la direzione per creare tutti i muri:
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
        Position pos = startPosition_;
        walls_.resize(length);
        walls_[0] = new Wall(pos, (char) enums::WallType::ANGLE);
        pos += posDirection_;
        for (int i = 1; i < length_; i++) {
            walls_[i] = new Wall(pos, (char) type);
            pos += posDirection_;
        }
    }

    WallSegment::~WallSegment() {
        for (int i = 0; i < length_; i++) {
            delete walls_[i];
        }
    }

    void WallSegment::render(WINDOW *win, bool force) {
        for (int i = 0; i < length_; i++) {
            walls_[i]->render(win, force);
        }
    }

    enums::CollisionType WallSegment::getCollisionType() {
        return enums::CollisionType::WALLSEGMENT;
    }

}; // namespace level