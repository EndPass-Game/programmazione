#pragma once

// struttura che mantiene la posizione di un elemento nello spazio
struct Position {
    int riga;
    int colonna;

    Position(int riga, int colonna);

    bool operator!=(const Position& pos) const;
    bool operator==(const Position& pos) const;
    bool operator<(const Position& pos) const;
    bool operator<=(const Position& pos) const;

    Position operator+(const Position& pos) const;
    Position operator-(const Position& pos) const;

    void operator=(const Position& pos);
    void operator+=(const Position& pos);
    void operator-=(const Position& pos);
};