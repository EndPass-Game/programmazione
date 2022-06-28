#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
namespace level {
    Level::Level(Player *player, Size size) {
        player_ = player;
        walls_ = datastruct::Vector<Wall *>(0);
        entities_ = datastruct::Vector<Entity *>(0);
        levelSize_ = size; 
        collider_ = new Collider(size);

        // TODO(ang): come creare le stanze? come gestire i muri?
    }

    Level::Level(Player *player, Size size, Level *oldlevel) : Level(player, size) {
        // TODO(ang): come fare a creare una porta?
        // 1. scegliere la posizione
        // 2. scegliere la direzione (verticale o orizzontale)
        // 3. creare la porta (quanti caratteri? 1/ 2?)
    }

    Level::~Level() {
        for (unsigned int i = 0; i < walls_.size(); i++) {
            delete walls_[i];
        }

        for (unsigned int i = 0; i < entities_.size(); i++) {
            delete entities_[i];
        }

        delete collider_;
    }	

    void Level::update() {
        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }
}; // namespace level