#include "loader/objects/enemy.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Enemy::load(FILE *file) {
        LoadObject::resetTransferred();

        // TODO(simo): la roba per decidere che tipo di enemy creare
        // ossia l'enum enemy type lo puoi utilizzare qui...
        // anche se non so quanto sia utile utilizzarlo se lo usi qui boh...
        
        // int numeroShooter;
        // fscanf(file, "%d", &numeroShooter);
        // this->loadedObjects_->resize(numeroShooter);
        // for (int i = 0; i < numeroShooter; i++) {
        //     Position startPosition;
        //     fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
        //     entities::Enemy *enemy = new entities::Shooter(startPosition);
        //     this->loadedObjects_->at(i) = enemy;
        // }
        
        int numeroKamikaze;
        fscanf(file, "%d", &numeroKamikaze);
        this->loadedObjects_->resize(numeroKamikaze);
        for (int i = 0; i < numeroKamikaze; i++) {
           Position startPosition;
           fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
           entities::Enemy *enemy = new entities::Kamikaze(startPosition);
           this->loadedObjects_->at(i) = enemy;
        }
    };
}  // namespace loader