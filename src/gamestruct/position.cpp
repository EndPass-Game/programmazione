#include "gamestruct/position.hpp"

Position::Position() :
    riga(0),
    colonna(0) {}

Position::Position(int riga, int colonna) {
    this->riga = riga;
    this->colonna = colonna;
}

bool Position::operator!=(const Position& pos) const {
    return riga != pos.riga || colonna != pos.colonna;
}

bool Position::operator==(const Position& pos) const {
    return riga == pos.riga && colonna == pos.colonna;
}

Position Position::operator*(int scale_factor) const {
    return Position(riga * scale_factor, colonna * scale_factor);
}

Position Position::operator+(const Position& pos) const {
    return Position(riga + pos.riga, colonna + pos.colonna);
}

Position Position::operator-(const Position& pos) const {
    return Position(riga - pos.riga, colonna - pos.colonna);
}

void Position::operator=(const Position& pos) {
    riga = pos.riga;
    colonna = pos.colonna;
}

void Position::operator*=(int scale_factor) {
    riga *= scale_factor;
    colonna *= scale_factor;
}

void Position::operator+=(const Position& pos) {
    riga += pos.riga;
    colonna += pos.colonna;
}

void Position::operator-=(const Position& pos) {
    riga -= pos.riga;
    colonna -= pos.colonna;
}

