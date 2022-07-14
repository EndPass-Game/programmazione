#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "enums/collision-type.hpp"
#include "collectables/artifact.hpp"
#include "manager/level.hpp"


namespace level {
    Level::Level(Size size) {
        //TODO(ang): mettere il giocatore davanti alla porta, o su punto di spawn prestabilito
        // (quando la stanza sarà nuova last player position conterrà il valore dell'entrata)
        lastPlayerPosition_ = Position(1,1); 

        segment_ = datastruct::Vector<DisplayableSegment *>();
        entities_ = datastruct::Vector<Entity *>(0);
        artifacts_ = datastruct::Vector<Artifact *>();

        // creazione dei muri esterni
        // TODO(ang): creare una funzione per creare i muri esterni
        // questo è temporaneo
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

        //inserimento in mappa degli artefatti
        artifacts_.push_back(new Artifact(6, Position(10,5)));
    }

    Level::Level(Size size, int oldLevelIdx) : Level(size) {
        segment_.push_back((DisplayableSegment *) new DoorSegment(
            Position(5, 0), enums::Direction::RIGHT, 5, oldLevelIdx, false));

    }

    Level::~Level() {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            delete segment_[i];
        }

        for (unsigned int i = 0; i < entities_.size(); i++) {
            delete entities_[i];
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            delete artifacts_[i];
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
        for (unsigned int i = 0; i<artifacts_.size(); i++){
            if(artifacts_[i]->getPosition() == pos){
                Artifact *c = artifacts_[i];
                artifacts_.remove(i);
                return (Collidable *) c;
            }
        }

        // TODO(simo): gestire altri oggetti di collisione
        // es: entity, ...
        return nullptr;
    }


    void Level::render(WINDOW *win, bool force) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->render(win, force);
        }
        
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->render(win, force);
        }

        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level