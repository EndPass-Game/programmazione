#pragma once

#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"

namespace collectables {

    class Power : public Displayable, public level::Collidable {
      private:
        int id_;  // apre la door locale con id = id

      public:
        /// costruttore che inizializza la variabile che definisce l'aumento di vità che darà l'artefatto e la sua posizione
        Power(Position posObj, int id);
        virtual ~Power() = default;

        int getId();

        /// override del metodo virtuale per restituire il tipo di oggetto
        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables