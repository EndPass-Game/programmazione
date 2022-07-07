#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "level/wall-segment.hpp"
#include "level/collision-object.hpp"
#include "enums/direction.hpp"
#include "enums/collision-type.hpp"

namespace level {
    Level::Level(Size size,Player* player):player_(player) {
        //TODO:(ang) muovere il player in lastPlayerPosition_ 
        // (quando la stanza sarà nuova last player position conterrà il valore dell'entrata)
        segments_ = datastruct::Vector<WallSegment *>();
        entities_ = datastruct::Vector<Entity *>(0);
        // creazione dei muri esterni
        using namespace enums; // Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN
        segments_.push_back(new WallSegment(Position(0, 0), Direction::RIGHT, size.colonna - 1));
        segments_.push_back(new WallSegment(Position(0, size.colonna - 1), Direction::DOWN, size.riga - 1));
        segments_.push_back(new WallSegment(Position(size.riga - 1, size.colonna - 1), Direction::LEFT, size.colonna - 1));
        segments_.push_back(new WallSegment(Position(size.riga - 1, 0), Direction::UP, size.riga - 1));

        // TODO(ang): rimuovere questo muro di prova che sto mettendo ora 
        segments_.push_back(new WallSegment(Position(0, size.colonna / 2), Direction::DOWN, size.riga / 2));
        // TODO(ang): gestire anche la creazione dei segmenti intermedi 
    }

    Level::Level(Size size, Level *oldlevel,Player *player) : Level(size,player) {
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
    }	

    bool Level::isPositionEmpty(Position pos) {
        return getCollisionObject(pos).type == enums::CollisionType::NONE;
    }

    CollisionObject Level::getCollisionObject(Position pos) {
        for (unsigned int i = 0; i < segments_.size(); i++) {
            if (segments_[i]->isPositionInSegment(pos)) {
                return CollisionObject(enums::CollisionType::WALLSEGMENT, (Collidable *) segments_[i]);
            }
        }

        // TODO(simo): gestire altri oggetti di collisione
        // es: entity, artefatti, ...
        return CollisionObject(enums::CollisionType::NONE, nullptr);
    }


    void Level::render(WINDOW *win, bool force) {

        for (unsigned int i = 0; i < segments_.size(); i++) {
            segments_[i]->render(win, force);
        }

        player_->clearLast(win);
        player_->render(win, force);
        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level