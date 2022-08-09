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

        // @brief renderizza il contenuto del livello
        // @param force se true rirenderizza anche quelli non modificati
        void render(WINDOW *win, bool force);

        // cancella tutto quanto printato su schermo 
        void clear(WINDOW *win);

        // @returns true se la posizione è vuota, false altrimenti
        bool isPositionEmpty(Position pos);

        // @returns l'oggetto di collisione alla data posizione
        Collidable *getCollision(Position pos);
    }; 
}; // namespace map