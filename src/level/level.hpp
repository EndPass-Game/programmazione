#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "datastruct/vector.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "loader/loader-handler.hpp"

namespace level {
    // contenere tutti i oggetti utili per il singolo livello
    class Level {
      private:
        datastruct::Vector<WallSegment> wallSegments_;
        datastruct::Vector<DoorSegment> doorSegments_;

        Position lastPlayerPosition_;
        datastruct::Vector<DisplayableSegment *> segment_;
        datastruct::Vector<Entity *> entities_;
        datastruct::Vector<collectables::Artifact> artifacts_;
        datastruct::Vector<collectables::Power> powers_;
        datastruct::Vector<Position> playerPositions_;

        Logger logger_ = Logger("level::Level");

      public:
        Level(loader::LoaderHandler *loader);
        Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx);

        ~Level() = default;

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
};  // namespace level