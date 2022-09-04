#pragma once

#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"

namespace collectables {

    class Power : public Displayable, public level::Collidable {
      private:
        int id_;  // apre la door locale con id = id

      public:
        /**
         * @brief Costruisce un nuovo oggetto power
         *
         * @param posObj la posizione dell'oggetto
         * @param id l'id dell'oggetto, deve essere collegato alla posta locale
         */
        Power(Position posObj, int id);

        virtual ~Power() = default;

        int getId();

        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables
