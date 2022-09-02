#include "entities/shooter.hpp"

#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "entities/weapon/bullet.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"
#include "enums/direction.hpp"

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
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        level::Level *level = levelManager->getLevel();
        if(canAttack(levelManager)){
            this->resetShootCoolDown();
            logger_.info("enemy firing a bullet");
            enums::Direction dir = findShootDirection(levelManager, currPosition, playerPosition);
            Position bulletPosition = findBulletPosition(dir);
            weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, dir, this->getAttack());
            level->addBullet(bullet);
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
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        if(currPosition.riga == playerPosition.riga){
            if(currPosition.colonna < playerPosition.colonna){
                if(LineFirable(currPosition.riga, currPosition.colonna + 1, playerPosition.colonna, levelManager)){
                    return true;
                }
            }
            else{
                if(LineFirable(currPosition.riga, playerPosition.colonna + 1, currPosition.colonna, levelManager)){
                    return true;
                }
            }
        }
        if(currPosition.colonna == playerPosition.colonna){
            if(currPosition.riga < playerPosition.riga){
                if(columnFirable(currPosition.colonna, currPosition.riga + 1, playerPosition.riga, levelManager)){
                    return true;
                }
            }
            else{
                if(columnFirable(currPosition.colonna, playerPosition.riga + 1, currPosition.riga, levelManager)){
                    return true;
                }
            }
        }
        return false;
    }

    enums::Direction Shooter::findShootDirection(manager::Level *levelManager, Position currPosition, Position playerPosition){
        if(currPosition.riga == playerPosition.riga){
            if(currPosition.colonna < playerPosition.colonna){
                return enums::Direction::RIGHT;
            }
            else{
                return enums::Direction::LEFT;
            }
        }
        if(currPosition.colonna == playerPosition.colonna){
            if(currPosition.riga < playerPosition.riga){
                return enums::Direction::DOWN;
            }
            else{
                return enums::Direction::UP;
            }
        }
        return enums::Direction::NONE;
    }

    Position Shooter::findBulletPosition(enums::Direction dir){
        switch(dir){
            case enums::Direction::RIGHT:
                return Position (this->getPosition().riga, this->getPosition().colonna + 1);
                break;
            case enums::Direction::LEFT:
                return Position (this->getPosition().riga, this->getPosition().colonna - 1);
                break;
            case enums::Direction::DOWN:
                return Position (this->getPosition().riga + 1, this->getPosition().colonna);
                break;
            case enums::Direction::UP:
                return Position (this->getPosition().riga - 1, this->getPosition().colonna);
                break;
            case enums::Direction::NONE:
                return Position (1,1);
                break;
        }
        return Position (1,1);
    }
    
}