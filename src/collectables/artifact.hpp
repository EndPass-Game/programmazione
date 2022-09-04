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
        /**
         * @brief Costruttore di un oggetto artefatto
         *
         * @param lifeUpgrade_ descrive quanto l'artefatto aumenta la vita
         * @param posObj descrive la posizione dell'artefatto
         */
        Artifact(int lifeUpgrade_, Position posObj);

        virtual ~Artifact() = default;

        int getLifeUpgrade();

        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables
