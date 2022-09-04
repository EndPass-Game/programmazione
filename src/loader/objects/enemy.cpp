#include "loader/objects/enemy.hpp"

#include "entities/enemy.hpp"
#include "entities/shooter.hpp"
#include "entities/kamikaze.hpp"
#include "gamestruct/position.hpp"

namespace loader {
    void Enemy::load(FILE *file) {
        LoadObject::resetTransferred();
        // di fatto deve ritornare un vettore di enemy quindi credo sia più giusto tenerlo qui
        // piuttosto di fare due file separati

        int numeroKamikaze;
        fscanf(file, "%d", &numeroKamikaze);
        this->loadedObjects_->resize(numeroKamikaze);
        for (int i = 0; i < numeroKamikaze; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            entities::Enemy *enemy = new entities::Kamikaze(startPosition);
            this->loadedObjects_->at(i) = enemy;
        }

        int numeroShooter;
        fscanf(file, "%d", &numeroShooter);
        this->loadedObjects_->resize(numeroKamikaze + numeroShooter);
        for (int i = 0; i < numeroShooter; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            entities::Enemy *enemy = new entities::Shooter(startPosition);
            this->loadedObjects_->at(numeroKamikaze + i) = enemy;
        }
    };
}  // namespace loader