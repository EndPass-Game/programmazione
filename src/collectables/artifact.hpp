/*
Descrizione:
aumentano la vita
Possiamo fargli fare altre cose? si in futuro
fanno altre cose? ma non credo, non per ora
*/
#pragma once

#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"

namespace collectables {

    class Artifact : public Displayable, public level::Collidable {
      private:
        int lifeUpgrade_;

      public:
        // costruttore che inizializza la variabile che definisce l'aumento di vità che darà l'artefatto e la sua posizione
        Artifact(int lifeUpgrade_, Position posObj);
        virtual ~Artifact() = default;
        int getLifeUpgrade();

        // override del metodo virtuale per restituire il tipo di oggetto
        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables