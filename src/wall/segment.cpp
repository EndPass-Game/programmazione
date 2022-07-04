#include "segment.hpp"

#include <ncurses.h>

#include "enums/wall_type.hpp"

namespace wall {
    Segment::Segment() : startPosition_(0,0) {
        walls_.clear(); 
        length_ = 0;
        direction_ = enums::Direction::NONE;
    }

    Segment::Segment(Position start_position, enums::Direction direction, int length) : startPosition_(start_position) {
        direction_ = direction;
        length_ = length;
        // if (length_ <= 0 )
        walls_.resize(length_);

        Position pos = startPosition_;
        // scegliendo la direzione per creare tutti i muri:
        enums::WallType type = enums::WallType::EMPTY;
        Position pos_adder(0, 0); 
        switch (direction) {
            case enums::Direction::UP:
                pos_adder = Position(-1, 0);
                type = enums::WallType::VERT;
                break;
            case enums::Direction::DOWN:
                pos_adder = Position(1, 0);
                type = enums::WallType::VERT;
                break;
            case enums::Direction::LEFT:
                pos_adder = Position(0, -1);
                type = enums::WallType::HORIZ;
                break;
            case enums::Direction::RIGHT:
                pos_adder = Position(0, 1);
                type = enums::WallType::HORIZ;
                break;
            default:
                break;
        }
        walls_[0] = new Wall(pos, (char) enums::WallType::ANGLE);
        pos += pos_adder;
        for (int i = 1; i < length_; i++) {
            walls_[i] = new Wall(pos, (char) type);
            pos += pos_adder;
        }
    }

    Segment::~Segment() {
        for (int i = 0; i < length_; i++) {
            delete walls_[i];
        }
    }

    void Segment::render(WINDOW *win, bool force) {
        for (int i = 0; i < length_; i++) {
            walls_[i]->render(win, force);
        }
    }

    bool Segment::hasCollided(Position pos) {
        for (int i = 0; i < length_; i++) {
            if (walls_[i]->getPosition() == pos) {
                return true;
            }
        }
        return false; // non ha colpito nessuno dei muri
    }
}; // namespace wall