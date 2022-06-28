#pragma once 

#include "datastruct/vector.hpp"
#include "level/enums/state.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"

namespace level {
    // il collider è una rapresentazione interna del livello, non è una struttura dati che viene mostrata a schermo
    // ha il compito di gestire ogni collisione tra oggetti di tipo Displayable
    class Collider {
      private:
        datastruct::Vector<datastruct::Vector<enums::State>> state_; // TODO(gio): esiste un modo per risparmiare memo?
        Size size_; 
      public:
        Collider();
        Collider(Size size);
        ~Collider();

        enums::State getState(Position pos) const;
        bool hasCollided(Position pos) const;
        void setState(Position pos, enums::State state);
        void moveState(Position oldpos, Position newpos);
    }; // namespace coollider
}; // namespace level