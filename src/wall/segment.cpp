#include "segment.hpp"

#include <ncurses.h>

#include "enums/wall_type.hpp"

namespace wall {
    Segment::Segment() {
        walls_.clear(); 
        start_position_ = Position(0, 0);
        length_ = 0;
        direction_ = enums::Direction::NONE;
    }

    Segment::Segment(Position start_position, enums::Direction direction, int length) {
        start_position_ = start_position;
        direction_ = direction;
        length_ = length;
        walls_.resize(length_);

        Position pos = start_position_;

        // scegliendo la direzione per creare tutti i muri:
        enums::WallType type = enums::WallType::EMPTY;
        Position pos_adder(0, 0); 
        switch (direction) {
            case enums::Direction::UP:
                pos_adder = Position(1, 0);
                type = enums::WallType::VERT;
                break;
            case enums::Direction::DOWN:
                pos_adder = Position(-1, 0);
                type = enums::WallType::VERT;
                break;
            case enums::Direction::LEFT:
                pos_adder = Position(0, 1);
                type = enums::WallType::HORIZ;
                break;
            case enums::Direction::RIGHT:
                pos_adder = Position(0, -1);
                type = enums::WallType::HORIZ;
                break;
            default:
                break;
        }

        for (int i = 0; i < length_; i++) {
            walls_[i] = Wall(pos, (char) type);
            pos += pos_adder;
        }
    }

    void Segment::render(WINDOW *win) {
        for (int i = 0; i < length_; i++) {
            walls_[i].render(win);
        }
    }
}; // namespace wall