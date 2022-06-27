#include "gamestruct/position.hpp"

void Position::operator=(const Position& pos) {
    riga = pos.riga;
    colonna = pos.colonna;
}

bool Position::operator!=(const Position& pos) {
    return riga != pos.riga || colonna != pos.colonna;
}

bool Position::operator==(const Position& pos) {
    return riga == pos.riga && colonna == pos.colonna;
}

bool Position::operator<(const Position& pos) {
    return riga < pos.riga && colonna < pos.colonna;
}