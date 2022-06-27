#include "gamestruct/position.hpp"

void Position::operator=(const Position& pos) {
    x = pos.x;
    y = pos.y;
}

bool Position::operator!=(const Position& pos) {
    return x != pos.x || y != pos.y;
}

bool Position::operator==(const Position& pos) {
    return x == pos.x && y == pos.y;
}

bool Position::operator<(const Position& pos) {
    return x < pos.x && y < pos.y;
}