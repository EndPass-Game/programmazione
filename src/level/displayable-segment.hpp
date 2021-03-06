#pragma once 

#include <ncurses.h>

#include "level/collidable.hpp"
#include "level/segment.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/displayable.hpp"
#include "enums/direction.hpp"

namespace level {
    // classe che rappresenta un segmento di elementi visibili
    class DisplayableSegment: public Segment, public Collidable {
      protected:
        // vettore dei oggetti mostrato a schermo
        datastruct::Vector<Displayable *> displayables_;
      public: 
        // segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla
        DisplayableSegment(); 
        // crea un segmento di lunghezza length, in posizione startPosition di direzione direction
        // Esempio: DisplayableSegment(Position(0, 0), enums::Direction::RIGHT, 10)
        // crea un segmento di 10 muri in posizione (0, 0) e direzione a destra che printata a schermo è
        // OOOOOOOOOO  
        DisplayableSegment(Position start_position, enums::Direction direction, int length);
        virtual ~DisplayableSegment(); 

        virtual void render(WINDOW *win, bool force);

        // pure virtual function che restituisce il tipo di collisione 
        // previene la creazione di DisplayableSegment da sé, ma solo i suoi derivati
        // che implementano questa funzione con il tipo di collisione appropriato
        virtual enums::CollisionType getCollisionType() = 0; 
    }; // class DisplayableSegment
}; // namespace level