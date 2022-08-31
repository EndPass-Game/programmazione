#include "level/level.hpp"

#include "collectables/power.hpp"
#include "datastruct/vector.hpp"
#include "entities/enemy.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "enums/collision-type.hpp"
#include "gamestruct/size.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.hpp"

namespace level {
    Level::Level(loader::LoaderHandler *loader)
        : lastPlayerPosition_(1, 1),
          segment_(),
          artifacts_(),
          powers_(),
          enemies_(),
          bullets_(),
          playerPositions_(),
          numOfDoors_(0),
          logger_("level::Level") {
        datastruct::Vector<WallSegment *> *segments = nullptr;
        segments = loader->wallLoader.getLoadedObjects();
        if (segments != nullptr) {
            for (unsigned int i = 0; i < segments->size(); i++) {
                segment_.push_back((DisplayableSegment *) segments->at(i));
            }
        }

        datastruct::Vector<DoorSegment *> *doors = nullptr;
        doors = loader->doorLoader.getLoadedObjects();
        if (doors != nullptr) {
            numOfDoors_ = doors->size();
            for (unsigned int i = 0; i < doors->size(); i++) {
                segment_.push_back((DisplayableSegment *) doors->at(i));
            }
        }

        // avremmo una invalid-read se playerPositions_.size() == 0, ma questo non dovrebbe mai
        // succedere per checks in loader::LoaderHandler (in particolare quello sulle porte)
        playerPositions_ = loader->doorLoader.getPlayerPositions();
        lastPlayerPosition_ = playerPositions_.at(0);

        datastruct::Vector<collectables::Artifact *> *artifacts = nullptr;
        artifacts = loader->artifactLoader.getLoadedObjects();
        if (artifacts != nullptr) {
            for (unsigned int i = 0; i < artifacts->size(); i++) {
                artifacts_.push_back(artifacts->at(i));
            }
        }

        datastruct::Vector<collectables::Power *> *powers = nullptr;
        powers = loader->powerLoader.getLoadedObjects();
        if (powers != nullptr) {
            for (unsigned int i = 0; i < powers->size(); i++) {
                powers_.push_back(powers->at(i));
            }
        }

        datastruct::Vector<entities::Enemy *> *enemies = nullptr;
        enemies = loader->enemyLoader.getLoadedObjects();
        if (enemies != nullptr) {
            for (unsigned int i = 0; i < enemies->size(); i++) {
                enemies_.push_back(enemies->at(i));
            }
        }
    }

    Level::Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx)
        : Level(loader) {
        logger_.debug("creating level pointing to leveldIdx: %d", oldLevelIdx);

        DoorSegment *chosenDoor = nullptr;

        // questa parte assume che le porte siano tutte nell'ultima parte del segmento:
        for (unsigned int i = segment_.size() - numOfDoors_; i < segment_.size(); i++) {
            DoorSegment *door = (DoorSegment *) segment_.at(i);
            if (door->getFacingDir() == direction) {
                chosenDoor = door;
                lastPlayerPosition_ = playerPositions_[i - (segment_.size() - numOfDoors_)];
                break;
            }
        }

        if (chosenDoor == nullptr) {
            logger_.warning("no door found for direction %d", direction);
            logger_.info("choosing random door");
            int doorNumber = rand() % numOfDoors_;
            chosenDoor = (DoorSegment *) segment_.at(segment_.size() - numOfDoors_ + doorNumber);
            lastPlayerPosition_ = playerPositions_[doorNumber];
        }

        chosenDoor->setNextLevelIdx(oldLevelIdx);
        chosenDoor->openDoor();
    }

    Level::~Level() {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            delete segment_[i];
        }

        for (unsigned int i = 0; i < enemies_.size(); i++) {
            delete enemies_[i];
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            delete artifacts_[i];
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            delete powers_[i];
        }

        for (unsigned int i = 0; i < bullets_.size(); i++) {
            delete bullets_[i];
        }
        for (unsigned int i = 0; i < bullets_.size(); i++) {
            delete enemies_[i];
        }
    }

    Position Level::getLastPlayerPosition() {
        return lastPlayerPosition_;
    }

    void Level::setLastPlayerPosition(Position pos) {
        lastPlayerPosition_ = pos;
    }

    bool Level::isPositionEmpty(Position pos, manager::Level *levelManager) {
        return getCollision(pos, levelManager) == nullptr;
    }

    Collidable *Level::getCollision(Position pos, manager::Level *levelManager) const {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            if (segment_[i]->isPositionInSegment(pos)) {
                return (Collidable *) segment_[i];
            }
        }
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            if (artifacts_[i]->getPosition() == pos) {
                collectables::Artifact *c = artifacts_[i];
                return (Collidable *) c;
            }
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            if (powers_[i]->getPosition() == pos) {
                collectables::Power *c = powers_[i];
                return (Collidable *) c;
            }
        }
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            if (enemies_[i]->getPosition() == pos) {
                entities::Enemy *c = enemies_[i];
                return (Collidable *) c;
            }
        }
        if (levelManager->getPlayer()->getPosition() == pos){
            Player *c = levelManager->getPlayer();
            return (Collidable *) c;
        }
        return nullptr;
    }

    datastruct::Vector<collectables::Power *> Level::getPowers() {
        return powers_;
    }

    datastruct::Vector<collectables::Artifact *> Level::getArtifacts() {
        return artifacts_;
    }

    void Level::addBullet(weapon::Bullet *bullet) {
        bullets_.push_back(bullet);
    }

    void Level::renderBullets(WINDOW *win, manager::Level *levelManager) {
        unsigned int i = 0;
        while (i < bullets_.size()) {
            Position bulletNextPosition = bullets_[i]->getNextPosition();
            Position bulletPosition = bullets_[i]->getPosition();
            Collidable *collision = getCollision(bulletNextPosition, levelManager);
            enums::CollisionType type = enums::CollisionType::NONE;
            if (collision != nullptr) type = collision->getCollisionType();
            if (type == enums::CollisionType::ENTITY) {
                logger_.debug("bullet collision with %d", collision->getCollisionType());
                if (bullets_[i]->handleEntityHit((Entity *) collision)) {
                    if(collision == levelManager->getPlayer()){
                        levelManager->getLogQueue()->addEvent("Player sconfitto");
                        //TODO (gio): Reindirizzamento alla pagine di game over
                    }
                    else{
                        deleteEnemy(collision, win);
                        levelManager->getPlayer()->incrementScore(500);
                        levelManager->getLogQueue()->addEvent("Nemico sconfitto");
                    }
                } else {
                    if(collision == levelManager->getPlayer()){
                        levelManager->getLogQueue()->addEvent("Player colpito da un proiettile");
                    }
                    else{
                        levelManager->getLogQueue()->addEvent("Nemico colpito da un proiettile");
                    }
                    
                }

                bullets_[i]->clear(win);
                delete bullets_[i];
                bullets_.remove(i);
            } else {
                if (type == enums::CollisionType::NONE) {
                    bullets_[i]->move();
                    // evita la cancellazione del player guardando il carattere printato nello schermo attuale
                    if (mvwinch(win, bulletPosition.riga, bulletPosition.colonna) != 'P') {
                        bullets_[i]->clearLast(win);
                    }
                    bullets_[i]->render(win);
                    i++;
                } else {
                    bullets_[i]->clear(win);
                    delete bullets_[i];
                    bullets_.remove(i);
                }
            }
        }
    }

    void Level::deleteEnemy(Collidable *collision, WINDOW *win) {
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            if (collision == enemies_[i]) {
                enemies_[i]->clear(win);
                delete enemies_[i];
                enemies_.remove(i);
            }
        }
    }

    void Level::deletePower(int i) {
        powers_.remove(i);
    }

    void Level::deleteArtifact(int i) {
        artifacts_.remove(i);
    }

    void Level::enemyShoot(entities::Shooter *s, manager::Level *levelManager){
        Collidable *collision;
        bool firable = true;
        if(s->canShoot()){
            if(s->getPosition().riga == levelManager->getPlayer()->getPosition().riga){
                if(s->getPosition().colonna < levelManager->getPlayer()->getPosition().colonna){
                    for(int i = (s->getPosition().colonna + 1); i <  (levelManager->getPlayer()->getPosition().colonna); i++){
                        collision = getCollision(Position (s->getPosition().riga, i), levelManager);
                        enums::CollisionType type = enums::CollisionType::NONE;
                        if (collision != nullptr) type = collision->getCollisionType();
                        if(type != enums::CollisionType::NONE){
                            firable = false;
                        }
                    }
                    if(firable){
                        s->resetShootCoolDown();
                        logger_.info("enemy firing a bullet");
                        Position bulletPosition = Position(s->getPosition().riga, s->getPosition().colonna + 1);
                        weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::RIGHT, s->getAttack());
                        this->addBullet(bullet);
                    }
                }
                else{
                    for(int i = (s->getPosition().colonna - 1); i >  (levelManager->getPlayer()->getPosition().colonna); i--){
                        collision = getCollision(Position (s->getPosition().riga, i), levelManager);
                        enums::CollisionType type = enums::CollisionType::NONE;
                        if (collision != nullptr) type = collision->getCollisionType();
                        if(type != enums::CollisionType::NONE){
                            firable = false;
                        }
                    }
                    if(firable){
                        s->resetShootCoolDown();
                        logger_.info("enemy firing a bullet");
                        Position bulletPosition = Position(s->getPosition().riga, s->getPosition().colonna - 1);
                        weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::LEFT, s->getAttack());
                        this->addBullet(bullet);
                    }
                }
            }
            if(s->getPosition().colonna == levelManager->getPlayer()->getPosition().colonna){
                if(s->getPosition().riga < levelManager->getPlayer()->getPosition().riga){
                    for(int i = (s->getPosition().riga + 1); i <  (levelManager->getPlayer()->getPosition().riga); i++){
                        collision = getCollision(Position (i, s->getPosition().colonna), levelManager);
                        enums::CollisionType type = enums::CollisionType::NONE;
                        if (collision != nullptr) type = collision->getCollisionType();
                        if(type != enums::CollisionType::NONE){
                            firable = false;
                        }
                    }
                    if(firable){
                        s->resetShootCoolDown();
                        logger_.info("enemy firing a bullet");
                        Position bulletPosition = Position(s->getPosition().riga + 1, s->getPosition().colonna);
                        weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::DOWN, s->getAttack());
                        this->addBullet(bullet);
                    }
                }
                else{
                    for(int i = (s->getPosition().riga - 1); i >  (levelManager->getPlayer()->getPosition().riga); i--){
                        collision = getCollision(Position (i, s->getPosition().colonna), levelManager);
                        enums::CollisionType type = enums::CollisionType::NONE;
                        if (collision != nullptr) type = collision->getCollisionType();
                        if(type != enums::CollisionType::NONE){
                            firable = false;
                        }
                    }
                    if(firable){
                        s->resetShootCoolDown();
                        logger_.info("enemy firing a bullet");
                        Position bulletPosition = Position(s->getPosition().riga - 1, s->getPosition().colonna);
                        weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::UP, s->getAttack());
                        this->addBullet(bullet);
                    }
                }
            }
        }
        else{
            s->ShootCoolDown();
        }
    }

    // BUG: non capisco perché ma ora non funziona più nonostante non abbia cambiato nulla e fa attaccare il nemico se il player
    //      si ritrova sulla colonna o sulla riga di tiro per l'enemy, non su entrambe (che vorrebbe dire che è al massimo a distanza 1)
    void Level::enemiesAttack(WINDOW *win, manager::Level *levelManager) {
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            if(enemies_[i]->getEnemyType() == enums::EnemyType::KAMIKAZE){
                if ((levelManager->getPlayer()->getPosition().riga - enemies_[i]->getPosition().riga) <= 1 && (levelManager->getPlayer()->getPosition().riga - enemies_[i]->getPosition().riga) >= -1) {
                    if ((levelManager->getPlayer()->getPosition().colonna - enemies_[i]->getPosition().colonna) <= 1 && (levelManager->getPlayer()->getPosition().colonna - enemies_[i]->getPosition().colonna) >= -1) {
                        enemies_[i]->attack(levelManager->getPlayer());
                        if (levelManager->getPlayer()->isDead()) {
                            // TODO (gio?): implementare una finestra di gameover
                        }
                        levelManager->getLogQueue()->addEvent("Il nemico e' esploso");
                        enemies_[i]->clear(win);
                        delete enemies_[i];
                        enemies_.remove(i);
                    }
                }
            }
            else{
                if(enemies_[i]->getEnemyType() == enums::EnemyType::SHOOTER){
                    this->enemyShoot((entities::Shooter *) enemies_[i], levelManager);
                }
            }
            
        }
    }

    void Level::renderEnemies(WINDOW *win, manager::Level *levelManager) {
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            if (enemies_[i]->canMove()) {
                enemies_[i]->wander();
                enemies_[i]->move(levelManager);
                enemies_[i]->clearLast(win);
                enemies_[i]->render(win);
                enemies_[i]->resetCoolDown();
            }
            enemies_[i]->moveCoolDown();
        }
    }

    void Level::render(WINDOW *win, bool force, manager::Level *levelManager) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->render(win, force);
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->render(win, force);
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i]->render(win, force);
        }

        this->renderBullets(win, levelManager);
        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }

    void Level::clear(WINDOW *win) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->clear(win);
        }
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->clear(win);
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i]->clear(win);
        }
        for (unsigned int i = 0; i < bullets_.size(); i++) {
            // TODO: possibile bug che il proiettile resti bloccato nel punto in cui
            // abbiamo lasciato il livello?? è un bug??
            bullets_[i]->clear(win);
        }
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            enemies_[i]->clear(win);
        }
    }
};  // namespace level