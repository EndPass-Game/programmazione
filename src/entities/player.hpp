/*
Dati:
1. vite
2. posizione
3. danno

Funzioni
1. display
2. muovi
4. attacco
5. Interagisci (collectibles porte)
6. Mostra / non-mostrare Barra vita (?)

Altro
1. Inventario ( Classe apparte? )
*/
#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
// Player: classe che contiene il personaggio
class Player : public Entity {
  private:
    // TODO inventario
    int powers_;
    int score_ = 0;
    Logger logger_ = Logger("player");
    virtual void _handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door, Position pos);
    virtual void _handleWallCollision(manager::Level *levelManager, level::WallSegment *wall, Position pos);
    virtual void _handleEntityCollision(manager::Level *levelManager, Entity *entity, Position pos);
    virtual void _handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact, Position pos);
    virtual void _handlePowerCollision(manager::Level *levelManager, collectables::Power *power, Position pos);
    virtual void _handleNoneCollision(manager::Level *levelManager, Position pos);

  public:
    Player();

    // funzione che sarà chiamata dall'input del giocatore
    // TODO: ricerca il mostro da attaccare in un certo range
    // se trova applica il danno
    void attack();

    // TODO
    void pickup();

    void addPower();

    void removePower();

    int getPowers();

    int getScore();

    void incrementScore(int increment);
};