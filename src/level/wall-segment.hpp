#pragma once 

#include <ncurses.h>

#include "level/wall.hpp"
#include "level/segment.hpp"
#include "level/collidable.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"

namespace level {
    // classe che rappresenta un segmento di muri
    // inoltre i segmenti di muri sono oggetto di collisione per oggetti o entità. e collidable permette ciò
    class WallSegment: public Segment, public Collidable {
      private:
        // vettore dei muri mostrato a schermo
        datastruct::Vector<Wall *> walls_;
      public: 
        // segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla
        WallSegment(); 
        // crea un segmento di lunghezza length, in posizione startPosition di direzione direction
        // Esempio: Segment(Position(0, 0), enums::Direction::RIGHT, 10)
        // crea un segmento di 10 muri in posizione (0, 0) e direzione a destra che printata a schermo è
        // +---------  
        WallSegment(Position start_position, enums::Direction direction, int length);
        ~WallSegment(); 

        void render(WINDOW *win, bool force);
        virtual enums::CollisionType getCollisionType() override;
    }; // class WallSegment
}; // namespace level