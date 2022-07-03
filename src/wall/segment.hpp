#pragma once 

#include <ncurses.h>

#include "wall/wall.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"

namespace wall {
    // classe che rappresenta un segmento di muri
    class Segment {
      private:
        // vettore dei muri mostrato a schermo
        datastruct::Vector<Wall> walls_;
        // posizione del segmento
        Position startPosition_; 
        enums::Direction direction_;
        int length_;
      public: 
        // segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla
        Segment(); 

        // crea un segmento di lunghezza length, in posizione startPosition di direzione direction
        // Esempio: Segment(Position(0, 0), enums::Direction::RIGHT, 10)
        // crea un segmento di 10 muri in posizione (0, 0) e direzione a destra
        Segment(Position start_position, enums::Direction direction, int length);

        // usato per mostrare a schermo l'intero vettore dei muri presenti    
        void render(WINDOW *win, bool force);

        bool hasCollided(Position pos);
    }; // class segment
}; // namespace wall