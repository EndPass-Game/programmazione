#pragma once 

#include "datastruct/vector.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/size.hpp"
#include "wall/segment.hpp"

namespace level {
    // contenere tutti i oggetti utili per il singolo livello 
    class Level {
      private: 
        Player *player_; // TODO(ang): invece del player, vorrei tenere posizione del player lastPlayerPosition_; 
        datastruct::Vector<wall::Segment *> segments_;
        datastruct::Vector<Entity *> entities_; 
        Size levelSize_; 
      public: 
        // genera il livello con la size data (walls and entities) 
        Level(Size size);
        
        // genera il livello con una porta al livello precedente
        Level(Size size, Level *oldlevel);
        ~Level();

        Player *getPlayer();
        // applies all position changes (entities) 
        void render(WINDOW *win, bool force);
    }; 
}; // namespace map