#include "loader/objects/enemy.hpp"

#include "gamestruct/position.hpp"

namespace loader {
    void Enemy::load(FILE *file) {
        LoadObject::resetTransferred();

        int numeroNemici;
        fscanf(file, "%d", &numeroNemici);
        this->loadedObjects_->resize(numeroNemici);
        for (int i = 0; i < numeroNemici; i++) {
            Position startPosition;
            fscanf(file, "%d %d\n", &startPosition.riga, &startPosition.colonna);
            entities::Enemy *enemy = new entities::Enemy(startPosition);
            this->loadedObjects_->at(i) = enemy;
        }
    };
}  // namespace loader