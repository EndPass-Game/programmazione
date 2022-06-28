#pragma once 

#include "datastruct/vector.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/size.hpp"
#include "level/collider.hpp"
#include "wall/wall.hpp"

namespace level {
    class Level {
      private: 
        Player *player_; 
        datastruct::Vector<Wall *> walls_;
        datastruct::Vector<Entity *> entities_; 
        Size levelSize_; 
        Collider *collider_;
      public: 
        // genera il livello con la size data (walls and entities) 
        Level(Player *player, Size size);
        
        // genera il livello con una porta al livello precedente
        Level(Player *player, Size size, Level *oldlevel);
        ~Level();

        // applies all position changes (entities) 
        void update();
    }; 
}; // namespace map