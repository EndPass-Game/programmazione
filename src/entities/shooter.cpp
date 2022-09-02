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
        level::Level *level = levelManager->getLevel();
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        
        // TODO simo, c'è ancora bisogno di migliorare questa parte
        if(currPosition.riga == playerPosition.riga){
            if(currPosition.colonna < playerPosition.colonna){
                if(LineFirable(currPosition.riga, currPosition.colonna + 1, playerPosition.colonna, levelManager)){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga, currPosition.colonna + 1);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::RIGHT, this->getAttack());
                    level->addBullet(bullet);
                }
            }
            else{
                if(LineFirable(currPosition.riga, playerPosition.colonna + 1, currPosition.colonna, levelManager)){
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
                if(columnFirable(currPosition.colonna, currPosition.riga + 1, playerPosition.riga, levelManager)){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga + 1, currPosition.colonna);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::DOWN, this->getAttack());
                    level->addBullet(bullet);
                }
            }
            else{
                if(columnFirable(currPosition.colonna, playerPosition.riga + 1, currPosition.riga, levelManager)){
                    this->resetShootCoolDown();
                    logger_.info("enemy firing a bullet");
                    Position bulletPosition = Position(currPosition.riga - 1, currPosition.colonna);
                    weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, enums::Direction::UP, this->getAttack());
                    level->addBullet(bullet);
                }
            }
        }
    }

    bool Shooter::LineFirable(int line, int begin, int finish, manager::Level *levelManager){
        level::Collidable *collision;
        for(int i = begin; i < finish; i++){
            collision = levelManager->getLevel()->getCollision(Position(line, i), levelManager);
            enums::CollisionType type = enums::CollisionType::NONE;
            if (collision != nullptr) type = collision->getCollisionType();
            if(type != enums::CollisionType::NONE){
                return false;
            }
        }
        return true;
    }

    bool Shooter::columnFirable(int column, int begin, int finish, manager::Level *levelManager){
        level::Collidable *collision;
        for(int i = begin; i < finish; i++){
            collision = levelManager->getLevel()->getCollision(Position(i, column), levelManager);
            enums::CollisionType type = enums::CollisionType::NONE;
            if (collision != nullptr) type = collision->getCollisionType();
            if(type != enums::CollisionType::NONE){
                return false;
            }
        }
        return true;
    }

    bool Shooter::canAttack(manager::Level *levelManager){
        return false;
    }
    
}