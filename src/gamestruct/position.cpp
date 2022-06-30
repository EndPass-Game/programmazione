#include "gamestruct/position.hpp"

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


Position Position::operator+(const Position& pos) const {
    return Position(riga + pos.riga, colonna + pos.colonna);
}

Position Position::operator-(const Position& pos) const {
    return Position(riga - pos.riga, colonna - pos.colonna);
}

void Position::operator=(const Position& pos){
    riga = pos.riga;
    colonna = pos.colonna;
}

void Position::operator+=(const Position& pos){
    riga += pos.riga;
    colonna += pos.colonna;
}

void Position::operator-=(const Position& pos) {
    riga -= pos.riga;
    colonna -= pos.colonna;
}

