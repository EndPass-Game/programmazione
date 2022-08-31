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

        /// @brief Distruttore generato dal compilatore
        virtual ~Power() = default;

        int getId();

        /**
         * @brief Get the Collision Type enum
         * 
         * @return enums::CollisionType il tipo di collisione impostata per l'oggetto
         */
        virtual enums::CollisionType getCollisionType() override;
    };

}  // namespace collectables
