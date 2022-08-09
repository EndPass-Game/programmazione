#pragma once 

#include "datastruct/vector.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/logger.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "collectables/artifact.hpp"
#include "loader/loader-handler.hpp"
#include "collectables/power.hpp"

namespace level {
    // contenere tutti i oggetti utili per il singolo livello 
    class Level {
      private: 
        Position lastPlayerPosition_;
        datastruct::Vector<DisplayableSegment *> segment_;
        datastruct::Vector<Artifact *> artifacts_;
        datastruct::Vector<Power *> powers_;
        datastruct::Vector<Entity *> entities_; 
        int numOfDoors_; // numero di porte nel livello
        
        Logger logger_ = Logger("level::Level");
      public: 
        Level(loader::LoaderHandler *loader); 
        Level(loader::LoaderHandler *loader, int oldLevelIdx); 
        ~Level();

        // restituisce la posizione dell'ultimo player
        Position getLastPlayerPosition();
        
        // setta la posizione dell'ultimo player
        void setLastPlayerPosition(Position pos);


        // applies all position changes (entities) 
        void render(WINDOW *win, bool force);

        // returns true if the position is Empty, false otherwise
        bool isPositionEmpty(Position pos);

        // returns the collision object at the given position
        Collidable *getCollision(Position pos);
    }; 
}; // namespace map