#pragma once 

#include <ncurses.h>

#include "level/wall.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"

namespace level {
    // classe astratta che rappresenta un qualunque segmento parallelo a 
    // un asse principale x,y
    // inoltre i segmenti sono oggetto di collisione per oggetti o entità. e collidable permette ciò
    class Segment {
      protected:
        Position startPosition_; 
        // end position è la posizione dell'ultimo muro. 
        // È ricavato dalla startPosition_ e la direzione_ e length_, si sceglie
        // di non proporre un costruttore per posizioni iniziali e finali per imporre l'essere parallelo
        // a un asse 
        Position endPosition_; 
        Position posDirection_; // versore per indicare la direzione
        int length_;
      public: 
        Segment(); 
        Segment(Position start_position, enums::Direction direction, int length);
        virtual ~Segment(); 

        bool isPositionInSegment(Position pos);
    }; // class segment
}; // namespace level