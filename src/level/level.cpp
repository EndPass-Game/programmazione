#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "enums/collision-type.hpp"


namespace level {
    Level::Level(Size size) {
        //TODO(ang): mettere il giocatore davanti alla porta, o su punto di spawn prestabilito
        // (quando la stanza sarà nuova last player position conterrà il valore dell'entrata)
        lastPlayerPosition_ = Position(1,1); 

        segment_ = datastruct::Vector<DisplayableSegment *>();
        // creazione dei muri esterni
        using namespace enums; // Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN
        segment_.push_back((DisplayableSegment *) new WallSegment(
            Position(0, 0), Direction::RIGHT, size.colonna - 1));
        segment_.push_back((DisplayableSegment *) new DoorSegment(
            Position(0, size.colonna - 1), Direction::DOWN, 5));
        segment_.push_back((DisplayableSegment *) new WallSegment(
            Position(5, size.colonna - 1), Direction::DOWN, size.riga - 6));
        segment_.push_back((DisplayableSegment *) new WallSegment(
            Position(size.riga - 1, size.colonna - 1), Direction::LEFT, size.colonna - 1));
        segment_.push_back((DisplayableSegment *) new WallSegment(
            Position(size.riga - 1, 0), Direction::UP, size.riga - 1));
        // TODO(ang): rimuovere questo muro di prova che sto mettendo ora 
        segment_.push_back((DisplayableSegment *) new WallSegment(
            Position(0, size.colonna / 2), Direction::DOWN, size.riga / 2));
        // TODO(ang): gestire anche la creazione dei segmenti intermedi 
    }

    Level::Level(Size size, Level *oldlevel) : Level(size) {
        // TODO(ang): come fare a creare una porta?
        // 1. scegliere la posizione
        // 2. scegliere la direzione (verticale o orizzontale)
        // 3. creare la porta (quanti caratteri? 1/ 2?)
    }

    Level::~Level() {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            delete segment_[i];
        }

        for (unsigned int i = 0; i < entities_.size(); i++) {
            delete entities_[i];
        }
    }	

    Position Level::getLastPlayerPosition() {
        return lastPlayerPosition_;
    }

    void Level::setLastPlayerPosition(Position pos) {
        lastPlayerPosition_ = pos;
    }

    bool Level::isPositionEmpty(Position pos) {
        return getCollision(pos) == nullptr;
    }

    Collidable *Level::getCollision(Position pos) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            if (segment_[i]->isPositionInSegment(pos)) {
                return (Collidable *) segment_[i];
            }
        }

        // TODO(simo): gestire altri oggetti di collisione
        // es: entity, artefatti, ...
        return nullptr;
    }


    void Level::render(WINDOW *win, bool force) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->render(win, force);
        }
        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level