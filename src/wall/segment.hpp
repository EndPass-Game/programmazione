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
        Position start_position_; 
        enums::Direction direction_;
        int length_;
      public: 
        Segment(); 
        Segment(Position start_position, enums::Direction direction, int length);

        // usato per mostrare a schermo l'intero vettore dei muri presenti    
        void render(WINDOW *win);
    }; // class segment
}; // namespace wall