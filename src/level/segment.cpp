#include "level/segment.hpp"

#include <ncurses.h>

namespace level {
    Segment::Segment() : 
        startPosition_(0,0),
        endPosition_(0,0) {
        length_ = 0;
        posDirection_ = Position(0, 0); // 0,0 per direzione invalida
    }

    Segment::Segment(Position startPosition, enums::Direction direction, int length) : 
        startPosition_(startPosition) {
        length_ = length;
        if (length_ <= 0 || direction == enums::Direction::NONE) {
            length_ = 1; // default value per valori non validi, corrisponde a singolo muro nella posizione startPosition_
        }
        Position pos = startPosition_;
        switch (direction) {
            case enums::Direction::UP:
                posDirection_ = Position(-1, 0);
                break;
            case enums::Direction::DOWN:
                posDirection_ = Position(1, 0);
                break;
            case enums::Direction::LEFT:
                posDirection_ = Position(0, -1);
                break;
            case enums::Direction::RIGHT:
                posDirection_ = Position(0, 1);
                break;
            default:
                posDirection_ = Position(0, 0);
                break;
        }
        // pos è il prossimo muro da creare, quindi pos - pos_adder è la posizione dell'ultimo muro creato
        endPosition_ = pos + posDirection_ * (length_ - 1);
    }

    Segment::~Segment() = default; 

    bool Segment::isPositionInSegment(Position pos) {
        if (startPosition_.colonna == pos.colonna) {
            int min = startPosition_.riga < endPosition_.riga ? startPosition_.riga : endPosition_.riga;
            int max = startPosition_.riga > endPosition_.riga ? startPosition_.riga : endPosition_.riga;
            return min <= pos.riga and pos.riga <= max;
        } else if (startPosition_.riga == pos.riga) {
            int min = startPosition_.colonna < endPosition_.colonna ? startPosition_.colonna : endPosition_.colonna;
            int max = startPosition_.colonna > endPosition_.colonna ? startPosition_.colonna : endPosition_.colonna;
            return min <= pos.colonna and pos.colonna <= max;
        } else {
            return false;
        }
    }
}; // namespace level