#include "entities/shooter.hpp"

#include <mutex>
#include <stdlib.h>

namespace entities{
    Shooter::Shooter()
        : Enemy('S'){}
    
    Shooter::Shooter(Position pos)
        :Enemy(pos, 3, 'S'),
        shootCoolDown_(0),
        shootCoolDownMax_(20){}

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
    
    enums::EnemyType Shooter::getEnemyType(){
        return enums::EnemyType::SHOOTER;
    }


}