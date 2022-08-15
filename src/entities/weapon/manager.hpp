#pragma once

#include <ncurses.h>

#include "entities/weapon/bullet.hpp"

namespace weapon {

    // classe utile a gestire tutte le armi presenti in un livello di gioco
    class Manager {
      private:
        datastruct::Vector<Bullet *> bullets_;

      public:
        Manager();
        ~Manager();

        // muove tutti i proiettili
        void move();

        // @brief aggiunge un proiettile al manager
        void createBullet(Position position, enums::Direction direction);
        void render(WINDOWS *window, bool force);
    };
}  // namespace weapon