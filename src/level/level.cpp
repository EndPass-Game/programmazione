#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "wall/segment.hpp"
#include "enums/direction.hpp"

namespace level {
    Level::Level(Size size) {
        player_ = new Player();
        segments_ = datastruct::Vector<wall::Segment *>();
        entities_ = datastruct::Vector<Entity *>(0);
        levelSize_ = size; 
        // creazione dei muri esterni
        segments_.push_back(new wall::Segment(Position(0, 0), enums::Direction::RIGHT, size.riga - 1));
        segments_.push_back(new wall::Segment(Position(size.riga, 0), enums::Direction::DOWN, size.colonna - 1));
        segments_.push_back(new wall::Segment(Position(size.riga, size.colonna), enums::Direction::LEFT, size.riga - 1));
        segments_.push_back(new wall::Segment(Position(0, size.colonna), enums::Direction::UP, size.colonna - 1));
        // TODO(ang): gestire anche la creazione dei segmenti intermedi 

    }

    Level::Level(Size size, Level *oldlevel) : Level(size) {
        // TODO(ang): come fare a creare una porta?
        // 1. scegliere la posizione
        // 2. scegliere la direzione (verticale o orizzontale)
        // 3. creare la porta (quanti caratteri? 1/ 2?)
    }

    Level::~Level() {
        for (unsigned int i = 0; i < segments_.size(); i++) {
            delete segments_[i];
        }

        for (unsigned int i = 0; i < entities_.size(); i++) {
            delete entities_[i];
        }
         
        delete player_;
    }	

    Player *Level::getPlayer() {
        return player_;
    }

    void Level::render(WINDOW *win, bool force) {
        for (unsigned int i = 0; i < segments_.size(); i++) {
            segments_[i]->render(win, force);
        }

        player_->move();
        player_->clearLast(win);
        player_->render(win, force);
        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level