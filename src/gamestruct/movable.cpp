#include "gamestruct/movable.hpp"

Movable::Movable(Position current, char displayChar)
    : Displayable(current, displayChar),
      nextPosition_(current),
      lastNotNullDirection_(enums::Direction::RIGHT),
      direction_(enums::Direction::NONE) {}

void Movable::setDirection(enums::Direction direction) {
    direction_ = direction;
}

enums::Direction Movable::getLastNotNullDirection() const {
    return lastNotNullDirection_;
}

Position Movable::getNextPosition() const {
    return nextPosition_;
}

Position Movable::_computeNextPosition(enums::Direction direction) {
    int newRiga = Displayable::getPosition().riga;
    int newColonna = Displayable::getPosition().colonna;
    switch (direction) {
        case enums::Direction::UP:
            newRiga -= 1;
            break;
        case enums::Direction::RIGHT:
            newColonna += 1;
            break;
        case enums::Direction::LEFT:
            newColonna -= 1;
            break;
        case enums::Direction::DOWN:
            newRiga += 1;
            break;
        case enums::Direction::NONE:
            break;
    }
    return Position(newRiga, newColonna);
}