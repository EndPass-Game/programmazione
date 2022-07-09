#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "level/wall-segment.hpp"
#include "level/door-segment.hpp"
#include "enums/direction.hpp"
#include "enums/collision-type.hpp"


namespace level {
    Level::Level(Size size) {
        //TODO(ang): mettere il giocatore davanti alla porta, o su punto di spawn prestabilito
        // (quando la stanza sarà nuova last player position conterrà il valore dell'entrata)
        lastPlayerPosition_ = Position(1,1); 

        wallSegments_ = datastruct::Vector<WallSegment *>();
        entities_ = datastruct::Vector<Entity *>(0);
        // creazione dei muri esterni
        using namespace enums; // Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN
        wallSegments_.push_back(new WallSegment(Position(0, 0), Direction::RIGHT, size.colonna - 1));
        wallSegments_.push_back(new WallSegment(Position(5, size.colonna - 1), Direction::DOWN, size.riga - 1));
        wallSegments_.push_back(new WallSegment(Position(size.riga - 1, size.colonna - 1), Direction::LEFT, size.colonna - 1));
        wallSegments_.push_back(new WallSegment(Position(size.riga - 1, 0), Direction::UP, size.riga - 1));
        doorSegments_.push_back(new DoorSegment(Position(0, size.colonna - 1), Direction::DOWN, 5));

        // TODO(ang): rimuovere questo muro di prova che sto mettendo ora 
        wallSegments_.push_back(new WallSegment(Position(0, size.colonna / 2), Direction::DOWN, size.riga / 2));
        // TODO(ang): gestire anche la creazione dei segmenti intermedi 
    }

    Level::Level(Size size, Level *oldlevel) : Level(size) {
        // TODO(ang): come fare a creare una porta?
        // 1. scegliere la posizione
        // 2. scegliere la direzione (verticale o orizzontale)
        // 3. creare la porta (quanti caratteri? 1/ 2?)
    }

    Level::~Level() {
        for (unsigned int i = 0; i < wallSegments_.size(); i++) {
            delete wallSegments_[i];
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
        for (unsigned int i = 0 ; i < doorSegments_.size(); i++) {
            if (doorSegments_[i]->isPositionInSegment(pos)) {
                return (Collidable *) doorSegments_[i];
            }
        }

        for (unsigned int i = 0; i < wallSegments_.size(); i++) {
            if (wallSegments_[i]->isPositionInSegment(pos)) {
                return (Collidable *) wallSegments_[i];
            }
        }

        // TODO(simo): gestire altri oggetti di collisione
        // es: entity, artefatti, ...
        return nullptr;
    }


    void Level::render(WINDOW *win, bool force) {
        for (unsigned int i = 0; i < wallSegments_.size(); i++) {
            wallSegments_[i]->render(win, force);
        }

        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level