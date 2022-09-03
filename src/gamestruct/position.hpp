#pragma once

// struttura che mantiene la posizione di un elemento nello spazio
struct Position {
    int riga;
    int colonna;

    //TODO:togliere questo commento

    Position();
    Position(int riga, int colonna);

    bool operator!=(const Position &pos) const;
    bool operator==(const Position &pos) const;

    Position operator*(int factor) const;
    Position operator+(const Position &pos) const;
    Position operator-(const Position &pos) const;

    void operator=(const Position &pos);
    void operator*=(int factor);
    void operator+=(const Position &pos);
    void operator-=(const Position &pos);
};