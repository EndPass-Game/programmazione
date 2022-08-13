#pragma once

#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
namespace collectables {

    class Power : public Displayable, public level::Collidable {
      private:
      public:
        // costruttore che inizializza la variabile che definisce l'aumento di vità che darà l'artefatto e la sua posizione
        Power(Position posObj = Position(1, 1));
        virtual ~Power() = default;
        // override del metodo virtuale per restituire il tipo di oggetto
        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables