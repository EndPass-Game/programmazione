#include "loader/objects/enemy.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Enemy::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroKamikaze;
        fscanf(file, "%d", &numeroKamikaze);
        this->loadedObjects_->resize(numeroKamikaze);
        for (int i = 0; i < numeroKamikaze; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            entities::Enemy *enemy = new entities::Kamikaze(startPosition);
            this->loadedObjects_->at(i) = enemy;
        }
        //TODO: da aggiungere la parte dello shooter
    };
}  // namespace loader