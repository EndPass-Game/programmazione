#pragma once

//struttura che mantiene la posizione di un elemento nello spazio
struct Position {
    int riga;
    int colonna;

    void operator=(const Position& pos);
    bool operator!=(const Position& pos);
    bool operator==(const Position& pos);
    bool operator<(const Position& pos);
};