#include "entities/shooter.hpp"

#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "entities/weapon/bullet.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

namespace entities{
    Shooter::Shooter()
        : Enemy('S'),  // TODO(simo) e shootcool down dove è?
        logger_("Shooter") {}
    
    Shooter::Shooter(Position pos)
        :Enemy(pos, 3, 'S'),
        shootCoolDown_(0),
        shootCoolDownMax_(20),
        logger_("Shooter") {}

    void Shooter::resetShootCoolDown(){
        shootCoolDown_ = shootCoolDownMax_;
    }

    void Shooter::ShootCoolDown(){
        shootCoolDown_--;
        if(shootCoolDown_ < 0) {
            shootCoolDown_ = 0;
        }
    }

    bool Shooter::canShoot(){
        return shootCoolDown_ == 0;
    }
    
    void Shooter::attack(manager::Level *levelManager) {
        if (!canShoot()) {
            this->ShootCoolDown();
            return;
        }

        level::Collidable *collision;
        level::Level *level = levelManager->getLevel();
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        bool firable = true;

        // TODO simo, c'è ancora bisogno di migliorare questa parte
        if(currPosition.riga == playerPosition.riga){
            if(currPosition.colonna < playerPosition.colonna){
                for(int i = (currPosition.colonna + 1); i <  (playerPosition.colonna); i++){
                    collision = level->getCollision(Position(currPosition.riga, i), levelManager);
                    enums::CollisionType type = enums::CollisionType::NONE;
                    if (collision != nullptr) type = collision->getCollisionType();
                    if(type != enums::CollisionType::NONE){
                        firable = false;
                    }
                }
                if(firable){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga, currPosition.colonna + 1);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::RIGHT, this->getAttack());
                    level->addBullet(bullet);
                }
            }
            else{
                for(int i = (currPosition.colonna - 1); i >  (playerPosition.colonna); i--){
                    collision = level->getCollision(Position (currPosition.riga, i), levelManager);
                    enums::CollisionType type = enums::CollisionType::NONE;
                    if (collision != nullptr) type = collision->getCollisionType();
                    if(type != enums::CollisionType::NONE){
                        firable = false;
                    }
                }
                if(firable){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga, currPosition.colonna - 1);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::LEFT, this->getAttack());
                    level->addBullet(bullet);
                }
            }
        }
        if(currPosition.colonna == playerPosition.colonna){
            if(currPosition.riga < playerPosition.riga){
                for(int i = (currPosition.riga + 1); i <  (playerPosition.riga); i++){
                    collision = level->getCollision(Position (i, currPosition.colonna), levelManager);
                    enums::CollisionType type = enums::CollisionType::NONE;
                    if (collision != nullptr) type = collision->getCollisionType();
                    if(type != enums::CollisionType::NONE){
                        firable = false;
                    }
                }
                if(firable){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga + 1, currPosition.colonna);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::DOWN, this->getAttack());
                    level->addBullet(bullet);
                }
            }
            else{
                for(int i = (currPosition.riga - 1); i >  (playerPosition.riga); i--){
                    collision = level->getCollision(Position (i, currPosition.colonna), levelManager);
                    enums::CollisionType type = enums::CollisionType::NONE;
                    if (collision != nullptr) type = collision->getCollisionType();
                    if(type != enums::CollisionType::NONE){
                        firable = false;
                    }
                }
                if(firable){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga - 1, currPosition.colonna);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::UP, this->getAttack());
                    level->addBullet(bullet);
                }
            }
        }
    }
}